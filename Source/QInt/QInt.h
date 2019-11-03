#include<iostream>
using namespace std;
#include<string>

class QInt
{
private:
	long long arrayBits[2];
public:
	QInt();
	QInt(string input, string radix);
	~QInt();

	QInt operator+( QInt &);
	QInt operator-( QInt &);
	QInt operator*( QInt &);
	QInt operator/( QInt &);
	QInt operator&(const QInt &)const;
	QInt operator|(const QInt &)const;
	QInt operator^(const QInt &)const;
	QInt operator<<(int);
	QInt operator>>(int);
	QInt RoR();
	QInt RoL();
	QInt Com_2();
	friend QInt operator~(const QInt &);
public:
	string Div2(string);
	string HexToBin_4bit(char);
	string BinToHex_4bit(string);
	string Plus(string, string);
	string Exp2(int);
	string Sub(string, string);
	string QIntToString(string);
	int Getbit(long long a, int i);
};