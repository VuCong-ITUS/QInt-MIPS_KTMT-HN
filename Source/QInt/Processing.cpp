#include"Processing.h"
#define	SUM 1
#define SUB  2
#define MULT 3
#define DIV 4

#define AND 5
#define OR 6
#define XOR 7
#define NOT 8

#define SHL 11
#define SHR 12
#define ROR 13
#define ROL 14

#define CONVERT 15

int Process(vector<string> s) // xử lí điều kiện đầu vào
{
	if (s[2] == "+")
		return 1;
	if (s[2] == "-")
		return 2;
	if (s[2] == "*")
		return 3;
	if (s[2] == "/")
		return 4;
	if (s[2] == "&")
		return 5;
	if (s[2] == "|")
		return 6;
	if (s[2] == "^")
		return 7;
	if (s[1] == "~")
		return 8;
	if (s[2] == "<<")
		return 11;
	if (s[2] == ">>")
		return 12;
	if (s[1] == "ror")
		return 13;
	if (s[1] == "rol")
		return 14;
	return 15;
}

string AddZero(string s, string radix) // thêm số 0 vào đầu chuỗi.
{
	if (radix == "2") // nếu là hệ 2 thì đủ 128 bit
	{
		while (s.length() < 128)
		{
			s = "0" + s;
		}
	}
	if (radix == "16") // nếu là hệ 16 thì đủ 32 bit
	while (s.length() < 32)
	{
		s = "0" + s;
	}
	return s;
}

string ReduceZero(string s) // xóa số 0 ở đầu chuỗi
{
	for (int i = 0; i < s.length(); i++)
	if (s[i] != '0')
	{
		s = s.substr(i);
		break;
	}
	return s;
}