
#include <iostream>
using namespace std;

class YCodec
{
public:
	YCodec();
	~YCodec();
	// char to hex code
	int Char2Hex(char ch);
	// hex to char
	char Hex2Char(unsigned int n);
	// num^index
	long MIndex(int num, int index);
	// string to hex code
	long String2Hex(char* string, int strlen);
	// hex to char*
	int Hex2String(long hex, char* string, int* slen);
	// hex to wchar_t code
	wchar_t Hex2Wchart(long hex);
	// UNICODEʮ�������ַ���ת����Ӣ��
	// hex string to wchar_t*
	int HexStr2WChars(char* hexstr, int hexstrlen, int eachchar, wchar_t* wchs, int* wchslen);
	// wchar_t to hex code
	long Wchart2Hex(wchar_t wch);
	// ��Ӣ��ת��UNICODEʮ�������ַ���
	// wchar_t* to char*(hex string)
	int Wchart2HexStr(wchar_t* wchs, int wchslen, int eachchar, char* hexstr, int* hexstrlen);

};