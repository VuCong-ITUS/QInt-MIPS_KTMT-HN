#include"QInt.h"
#include"Processing.h"
int main(int argc, char * argv[])
{		
	string input = argv[1];
	string output = argv[2];
	ifstream fin(input,ios::in);
	ofstream fout(output,ios::out);
	QInt a;
	vector<vector<string>> in;
	vector<string> out_result;
	string ot;
	string s1, s2;
	//đọc file
	string p;
	while (!fin.eof())
	{
		vector<string> s;
		int index = 0;
		string str;
		getline(fin, str, '\n');
		for (int i = 0; i < str.length(); i++)
		{
			if (str[i] == ' ')
			{
				p = str.substr(index, i - index);
				index = i + 1;
				s.push_back(p);
			}
			if (i == str.length() - 1)
			{
				p = str.substr(index, i - index + 1);
				s.push_back(p);
			}
		}
		in.push_back(s);
	}
	for (int i = 0; i < in.size(); i++)
	{
		switch (Process(in[i]))
		{
		case 1: //cộng
			s1 = AddZero(in[i][1], in[i][0]);	s2 = AddZero(in[i][3], in[i][0]);
			a = QInt(s1, in[i][0]) + QInt(s2, in[i][0]);
			break;
		case 2://trừ
			s1 = AddZero(in[i][1], in[i][0]);	s2 = AddZero(in[i][3], in[i][0]);
			a = QInt(s1, in[i][0]) - QInt(s2, in[i][0]);
			break;
		case 3://nhân
			s1 = AddZero(in[i][1], in[i][0]);	s2 = AddZero(in[i][3], in[i][0]);
			a = QInt(s1, in[i][0]) * QInt(s2, in[i][0]);
			break;
		case 4://chia
			s1 = AddZero(in[i][1], in[i][0]);	s2 = AddZero(in[i][3], in[i][0]);
			a = QInt(s1, in[i][0]) / QInt(s2, in[i][0]);
			break;
		case 5://and
			s1 = AddZero(in[i][1], in[i][0]);	s2 = AddZero(in[i][3], in[i][0]);
			a = QInt(s1, in[i][0]) & QInt(s2, in[i][0]);
			break;
		case 6://or
			s1 = AddZero(in[i][1], in[i][0]);	s2 = AddZero(in[i][3], in[i][0]);
			a = QInt(s1, in[i][0]) | QInt(s2, in[i][0]);
			break;
		case 7://xor
			s1 = AddZero(in[i][1], in[i][0]);	s2 = AddZero(in[i][3], in[i][0]);
			a = QInt(s1, in[i][0]) ^ QInt(s2, in[i][0]);
			break;
		case 8://not
			s1 = AddZero(in[i][2], in[i][0]);
			a = ~QInt(s1, in[i][0]);
			break;
		case 11: //SHL
			s1 = AddZero(in[i][1], in[i][0]);
			a = QInt(s1, in[i][0]);
			a = a << stoi(in[i][3]);
			break;
		case 12://SHR
			s1 = AddZero(in[i][1], in[i][0]);
			a = QInt(s1, in[i][0]);
			a = a >> stoi(in[i][3]);
			break;
		case 13://ROR
			s1 = AddZero(in[i][2], in[i][0]);
			a = QInt(s1, in[i][0]);
			a = a.RoR();
			break;
		case 14://ROL
			s1 = AddZero(in[i][2], in[i][0]);
			a = QInt(s1, in[i][0]);
			a = a.RoL();
			break;
		case 15://CONVERT
			s1 = AddZero(in[i][2], in[i][0]);
			a = QInt(s1, in[i][0]);
			break;
		}
		if (Process(in[i]) == 15)
		{
			if (in[i][1] == "2")// chuyển qua bù 2 nếu là dạng nhị phân
				a.Com_2();
			
			fout << ReduceZero(a.QIntToString(in[i][1])) << endl;
		}
		else
		{
			fout << ReduceZero(a.QIntToString(in[i][0])) << endl;
		}
	}
	return 0;
}