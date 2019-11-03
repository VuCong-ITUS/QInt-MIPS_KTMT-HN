#include"QInt.h"

QInt::QInt()
{
	arrayBits[0] = 0;
	arrayBits[1] = 0;
}

QInt::~QInt()
{
	//cout << "Destruction!!!";
}

int QInt::Getbit(long long a, int i)
{
	return (a >> i) & 1ULL;
}

QInt QInt::operator& (const QInt &And) const // phép and
{
	QInt res;
	res.arrayBits[0] = arrayBits[0] & And.arrayBits[0];
	res.arrayBits[1] = arrayBits[1] & And.arrayBits[1];
	return res;
}

QInt QInt::operator| (const QInt &Or) const // phép or
{
	QInt res;
	res.arrayBits[0] = arrayBits[0] | Or.arrayBits[0];
	res.arrayBits[1] = arrayBits[1] | Or.arrayBits[1];
	return res;
}

QInt QInt::operator^ (const QInt &Xor) const // phép xor
{
	QInt res;
	res.arrayBits[0] = arrayBits[0] ^ Xor.arrayBits[0];
	res.arrayBits[1] = arrayBits[1] ^ Xor.arrayBits[1];
	return res;
}

QInt operator~ (const QInt &Not)  // phép not
{
	QInt res;
	res.arrayBits[0] = ~Not.arrayBits[0];
	res.arrayBits[1] = ~Not.arrayBits[1];
	return res;
}

QInt QInt::operator+( QInt &Sum)  // tính tổng
{
	QInt res;
	int remember = 0;
	int tmp;
	for (int i = 1; i >= 0; i--) // chạy qua lần lượt hai mảng kiểu long long
	{
		for (int j = 0; j< 64; j++) // chạy qua lần lượt 64 bit của hai mảng 
		{
			if (Getbit(arrayBits[i], j) == 1 && Getbit(Sum.arrayBits[i], j) == 1) 
			{
				if (remember == 0)
				{
					tmp = 0;
				}
				else
				{
					tmp = 1;
				}
				remember = 1;
			}
			if ((Getbit(arrayBits[i], j) == 1 && Getbit(Sum.arrayBits[i], j) == 0) || (Getbit(arrayBits[i], j) == 0 && Getbit(Sum.arrayBits[i], j) == 1))
			{
				if (remember == 0)
				{
					tmp = 1;
				}
				else
				{
					tmp = 0;
					remember = 1;
				}
			}
			if ((Getbit(arrayBits[i], j) == 0 && Getbit(Sum.arrayBits[i], j) == 0))
			{
				if (remember == 0)
				{
					tmp = 0;
				}
				else
				{
					tmp = 1;
					remember = 0;
				}
			}
			if (tmp==1)
				res.arrayBits[i] |= (1ULL << j);
			else
				res.arrayBits[i] &= ~(1ULL << j);
		}
	}
	return res;
}

QInt QInt::Com_2() // hàm bù 2
{
	QInt a1;
	a1.arrayBits[1] |= (1ULL << 0); // tạo số nguyên QInt có giá trị là 1;
	return (~(*this) + a1);
}

QInt QInt::operator-(QInt &Sub) // phép tính trừ
{
	QInt res;
	QInt a2 = (*this);
	res = a2 + Sub.Com_2(); // cộng với số bù 2
	return res;
}

QInt QInt::operator*(QInt &Mult) // phép tính nhân
{
	QInt Q = (*this);
	QInt A;//tạo một biến A = 0;
	int k = 128;
	int Q0 = 0;
	A.arrayBits[0] = 0;
	A.arrayBits[1] = 0;
	while (k > 0)
	{
		int y = Getbit(Q.arrayBits[1], 0);
		if (y == 1 && Q0 == 0)
		{
			A = A - Mult;
		}
		if (y == 0 && Q0 == 1)
		{
			A = A + Mult;
		}
		int x = Getbit(A.arrayBits[1], 0);
		// xoay mảng [A,Q,Q0]
		A = A >> 1;
		Q = Q >> 1;
		if (x == 1)
			Q.arrayBits[0] |= (1ULL << 63);
		else
			Q.arrayBits[0] &= ~(1ULL << 63);
		Q0 = y;
		k--;
	}
	return Q;
}

QInt QInt::operator/(QInt &Div) // phép tính chia
{
	int count = 0;//tạo biến đếm đếm số dấu âm
	QInt Q = (*this);
	QInt A;//tạo một biến A;

	if (Getbit(Q.arrayBits[0], 63) == 1)// Đếm số dấu âm để biết dấu của kết quả
	{
		count = count + 1;
		Q = Q.Com_2();
	}
	if (Getbit(Div.arrayBits[0], 63) == 1)
	{
		count = count + 1;
		Div = Div.Com_2();
	}
	//Khởi tạo cho A gồm 128bit 0;
	A.arrayBits[0] = 0;
	A.arrayBits[1] = 0;
	int k = 128;
	while (k > 0)
	{
		//SHL mảng [A,Q]
		int x = Getbit(Q.arrayBits[0], 63);
		A = A << 1;
		Q = Q << 1;
		if (x == 1)
			A.arrayBits[1] |= 1ULL << 0;
		A = A - Div;
		if (Getbit(A.arrayBits[0], 63) == 1)//A<0;
		{
			Q.arrayBits[1] &= ~(1ULL << 0);// Q0=0;
			A = A + Div;
		}
		else
			Q.arrayBits[1] |= (1ULL << 0);// Q0=1;
		k--;
	}
	if (count == 1)
		Q = Q.Com_2();
	return Q;
}

QInt QInt::operator<<(int bit_number) // toán tử dịch trái
{
	for (int i = 0; i < bit_number; i++)
	{
		int x = Getbit(arrayBits[1], 63);
		arrayBits[0] <<= 1;
		arrayBits[1] <<= 1;
		if (x == 1)
			arrayBits[0] = (1ULL << 0) | arrayBits[0];
	}
	return *this;
}

QInt QInt::operator>>(int bit_number) // toán tử dịch phải
{
	for (int i = 0; i < bit_number; i++)
	{
		int x = Getbit(arrayBits[0], 0);
		arrayBits[0] >>= 1;
		arrayBits[1] >>= 1;
		if (x == 1)
			arrayBits[1] = (1ULL << 63) | arrayBits[1];
		else
			arrayBits[1] &= ~(1ULL << 63);
	}
	return *this;
}

QInt QInt::RoR() // phép xoay phải
{
	QInt result = (*this);
	int y = Getbit(result.arrayBits[1], 0);
	result = result >> 1;
	if (y == 1)
		result.arrayBits[0] = (1ULL << 63) | result.arrayBits[0];
	return result;
}

QInt QInt::RoL() // phép xoay trái 
{
	QInt result = (*this);
	int y = Getbit(result.arrayBits[0], 63);
	result = result << 1;
	if (y == 1)
		result.arrayBits[1] = (1ULL << 0) | result.arrayBits[1];
	return result;
}

string QInt::Div2(string s) // chia chuoi cho 2 xuat ra so du
{
		string res = "";
		int n = (int)s.length();
		int i = 0;

		string mod = "0";
		while (i != n)
		{
			int temp = stoi(mod + s[i]); // chuyen tu string qua int
			int sdu = temp % 2;
			int nguyen = temp / 2;
			res += char(nguyen + 48);
			mod = char(sdu + 48);
			i++;
		}
		if (res[0] == '0')
		{
			res.erase(0, 1);
		}
		return res;
}

string QInt::HexToBin_4bit(char s) // chuyển 1 kí tự ở hệ hex sang hệ bin
{
	string str;
	if (s == '0')
		str = "0000";
	if (s == '1')
		str = "0001";
	if (s == '2')
		str = "0010";
	if (s == '3')
		str = "0011";
	if (s == '4')
		str = "0100";
	if (s == '5')
		str = "0101";
	if (s == '6')
		str = "0110";
	if (s == '7')
		str = "0111";
	if (s == '8')
		str = "1000";
	if (s == '9')
		str = "1001";
	if (s == 'A')
		str = "1010";
	if (s == 'B')
		str = "1011";
	if (s == 'C')
		str = "1100";
	if (s == 'D')
		str = "1101";
	if (s == 'E')
		str = "1110";
	if (s == 'F')
		str = "1111";
	return str;
}

string QInt::BinToHex_4bit(string s) // chuyển 4 kí tự ở hệ bin sang hệ hex
{
	string str;
	if (s == "0000")
		str = "0";
	if (s == "0001")
		str = "1";
	if (s == "0010")
		str = "2";
	if (s == "0011")
		str = "3";
	if (s == "0100")
		str = "4";
	if (s == "0101")
		str = "5";
	if (s == "0110")
		str = "6";
	if (s == "0111")
		str = "7";
	if (s == "1000")
		str = "8";
	if (s == "1001")
		str = "9";
	if (s == "1010")
		str = "A";
	if (s == "1011")
		str = "B";
	if (s == "1100")
		str = "C";
	if (s == "1101")
		str = "D";
	if (s == "1110")
		str = "E";
	if (s == "1111")
		str = "F";
	return str;
}

string QInt::Plus(string a, string b) // cộng 2 chuỗi thập phân, trả về kết quả chuỗi
{
	string ans;
	int gaps = a.size() - b.size();
	if (gaps < 0)
	{
		gaps = abs(gaps);
		a.insert(0, gaps, '0');
	}
	else if (gaps > 0)
	{
		b.insert(0, gaps, '0');
	}
	int A, B, Ans, temp = 0;
	char c;
	for (size_t i = a.size(); i > 0; i--)
	{
		A = a[i - 1] - '0';
		B = b[i - 1] - '0';
		Ans = A + B + temp;
		temp = Ans / 10;
		c = Ans % 10 + '0';
		ans = c + ans;
	}
	if (temp > 0)
	{
		c = temp + '0';
		ans = c + ans;
	}
	return ans;
}

string QInt::Exp2(int n) // 2^n
{
	string ans = "1";
	for (int i = 0; i < n; i++)
	{
		ans = Plus(ans, ans);
	}
	return ans;
}

string QInt::Sub(string a, string b) // trừ 2 chuỗi thập phân, trả về kết quả chuỗi
{
	string ans = "";
	int gaps = a.size() - b.size();
	if (gaps < 0)
	{
		gaps = abs(gaps);
		a.insert(0, gaps, '0');
	}
	else if (gaps > 0)
	{
		b.insert(0, gaps, '0');
	}
	int A, B, Ans, temp = 0;
	for (int i = a.size(); i > 0; i--)
	{
		A = a[i - 1] - '0';
		B = (b[i - 1] - '0') + temp;
		temp = 0;
		if (B == 10)
		{
			B = 0;
			temp = 1;
		}
		if (A >= B)
		{
			Ans = A - B;
		}
		if (A < B)
		{
			Ans = 10 + A - B;
			temp = 1;
		}
		ans = to_string(Ans) + ans;
	}
	int j = 0;
	for (int i = 0; i < ans.length(); i++)
	{
		if (ans[i] != '0')
		{
			ans = ans.substr(i);
			break;
		}
		else
			j++;
		if (j == ans.length())
			ans = ans.substr(ans.length() - 1);
	}
	return ans;
}


QInt::QInt(string input, string radix)// chuyển từ chuỗi sang kiểu QInt
{

	if (radix == "2")
	{
		int index_arr;
		for (int i = 0; i < input.length(); i++)
		{
			int index_bit = (input.length() - 1 - i) % 64;
			int index = (input.length() - 1 - i) / 64;
			int bit_pos = input[i] - '0';
			if (index == 1)
				index_arr = 0;
			else
				index_arr = 1;
			if (bit_pos == 1)
				arrayBits[index_arr] |= (1ULL << index_bit);
			else
				arrayBits[index_arr] &= ~(1ULL << index_bit);
		}
	}
	if (radix == "16")
	{
		int index_arr;
		for (int i = 0; i<input.length(); i++)
		{
			
			for (int j = 0; j < 4; j++)
			{
				int index_bit = ((input.length() - 1) * 4 - i * 4 + 3 - j) % 64;
				int index = ((input.length() - 1) * 4 - i * 4 + 3 - j) / 64;
				int bit_pos = HexToBin_4bit(input[i])[j] - '0';
				if (index == 1)
					index_arr = 0;
				else
					index_arr = 1;
				if (bit_pos == 1)
					arrayBits[index_arr] |= (1ULL << index_bit);
				else
					arrayBits[index_arr] &= ~(1ULL << index_bit);
			}
		}
	}
	if (radix == "10")
	{
		int negative = 0;
		if (input[0] == '-')
		{
			negative = 1;
			input = input.substr(1);
		}
		int i = 128;
		while (input != "")
		{
			int len = input.length() - 1;
			int bit_pos = (input[len]-48) % 2;
			int index_bit = (128-i) % 64;
			int index_arr = i / 65;
			if (bit_pos == 1)
				arrayBits[index_arr] |= (1ULL << index_bit);
			else
				arrayBits[index_arr] &= ~(1ULL << index_bit);
			input = Div2(input);
			i--;
		}
		for (int j = i; j >0; j--)
		{
			int index_bit = (128-j) % 64;
			int index_arr = j / 65;
			arrayBits[index_arr] &= ~(1ULL << index_bit);
		}
		if (negative == 1)
			*this=(*this).Com_2();
	}
}

string QInt::QIntToString(string radix) // chuyển từ QInt sang chuỗi số
{
	string bin;
	for (int j = 0; j < 2; j++)
	{
		char a[64] = { 0 };
		unsigned long long mask = 0x8000000000000000;
		for (int i = 0; i < 64; i++)
		{
			if ((arrayBits[j] & mask) != 0)
				a[i] = 1;
			mask = mask >> 1;
		}
		for (int i = 0; i < 64; i++)
			bin = bin + to_string(a[i]);
	}
	if (radix == "2")
		return bin;
	if (radix == "10")
	{
		string dec="0";
		for (size_t i = 1; i < bin.length(); i++)
		{
			if (bin[i] != '0')
			{
				dec = Plus(dec, Exp2(128 - i - 1));
			}
		}
		if (bin[0] == '1')
		{
			dec = Sub(Exp2(127), dec);
			dec = '-' + dec;
		}
		return dec;
	}
	if (radix == "16")
	{
		string hex;
		string hex_4bit;
		for (int i = 0; i < 128; i=i+4)
		{
			hex_4bit = to_string(bin[i] - '0') + to_string(bin[i+1] - '0') + to_string(bin[i+2] - '0') + to_string(bin[i+3] - '0');
			hex = hex + BinToHex_4bit(hex_4bit);
		}
		return hex;
	}
}