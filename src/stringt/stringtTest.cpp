#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>
#include "stringt.h"

void showhex(const unsigned char* pData, int cb)
{
	std::cout << std::hex << std::uppercase;
	for(int i = 0; i < cb; i++)
		std::cout << (int)(pData[i]) << " ";
	std::cout << std::nouppercase << std::dec << std::endl;
}

template< typename _Elem >
void showhex(const std::basic_string< _Elem >& str)
{
	showhex((const unsigned char*)str.c_str(), str.size() * sizeof(_Elem));
}

template< typename _Elem >
void testContructor(const basic_string< _Elem >& str)
{
	std::cout << "== Contructor test" << std::endl;

	typename basic_string< _Elem >::_ThisX strX(str.c_str());
	std::cout << "   To _ElemX :         ";		showhex(strX);

	typename basic_string< _Elem >::_ThisY strY(str.c_str());
	std::cout << "   To _ElemY :         ";		showhex(strY);
}

template< typename _Elem >
void testAssignment(const basic_string< _Elem >& str)
{
	std::cout << "== Assignment test" << std::endl;

	typename basic_string< _Elem >::_ThisX strX;
	strX = str;
	std::cout << "   To _ElemX :         ";		showhex(strX);

	typename basic_string< _Elem >::_ThisY strY;
	strY = str;
	std::cout << "   To _ElemY :         ";		showhex(strY);
}

template< typename _Elem >
void testExplicit(const basic_string< _Elem >& str)
{
	std::cout << "== Explicit test (these are only _ElemY string.)" << std::endl;

	std::cout << "   ToY :               ";		showhex(str.toY());

	typename basic_string< _Elem >::_ThisY strY;
	std::cout << "   FromY :             ";		showhex(strY.fromY(str.c_str()));
}

template< typename _Elem >
void testUtf8(const basic_string< _Elem >& str)
{
	std::cout << "== UTF-8 test" << std::endl;

	std::string strUtf8 = str.toutf8();
	std::cout << "   To UTF-8 :          ";		showhex(strUtf8);

	typename basic_string< _Elem >::_ThisX strX;
	std::cout << "   _ElemX from UTF-8 : ";		showhex(strX.fromutf8(strUtf8));

	typename basic_string< _Elem >::_ThisY strY;
	std::cout << "   _ElemY from UTF-8 : ";		showhex(strY.fromutf8(strUtf8));
}

void testFormat(const string& str)
{
	std::cout << "== Format test" << std::endl;

	string strANSI;
	strANSI.format("%s", str.c_str());
	std::cout << "    char format :      ";		showhex(strANSI);

	wstring strUNICODE;
	strUNICODE.format("%s", str.c_str());
	std::cout << "    wchar_t format :   ";		showhex(strUNICODE);
}

void testFormat(const wstring& str)
{
	std::cout << "== Format test" << std::endl;

	string strANSI;
	strANSI.format(L"%s", str.c_str());
	std::cout << "    char format :      ";		showhex(strANSI);

	wstring strUNICODE;
	strUNICODE.format(L"%s", str.c_str());
	std::cout << "    wchar_t format :   ";		showhex(strUNICODE);
}

template< typename _Elem >
void test(const basic_string< _Elem >& str)
{
	std::cout << "From : ";		showhex(str);

	testContructor(str);
	testAssignment(str);
	testExplicit(str);
	testUtf8(str);
	testFormat(str);
}

int main(int argc, char* argv[])
{
	//setlocale(LC_ALL, "ko-KR");		// You should set locale information.
	setlocale(LC_ALL, "");

	// Sample text - Korean
	char szString[7] = { (char)0xB9, (char)0xAE, (char)0xC0, (char)0xDA, (char)0xBF, (char)0xAD, (char)0x00 };

	string strBaseANSI(szString);
	wstring strBaseUNICODE(szString);

	std::cout << "==== Test from ANSI string ====" << std::endl;
	test(strBaseANSI);
	std::cout << "===============================" << "\n\n";

	std::cout << "==== Test from UNCIDOE string ====" << std::endl;
	test(strBaseUNICODE);
	std::cout << "==================================" << "\n\n";

	return 0;
}
