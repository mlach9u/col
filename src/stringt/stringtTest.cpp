#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>
#include "stringt.h"

void showhex(const unsigned char* pData, int cb)
{
    std::cout << std::hex << std::uppercase;
    for (int i = 0; i < cb; i++)
        std::cout << (int)(pData[i]) << " ";
    std::cout << std::nouppercase << std::dec << std::endl;
}

template< typename _Elem >
void showhex(const std::basic_string< _Elem > & str)
{
    showhex((const unsigned char*)str.c_str(), (int)(str.size() * sizeof(_Elem)));
}

template< typename _Elem >
void testConstructor(const basic_string< _Elem > & str)
{
    std::cout << "== Constructor test" << std::endl;

    typename basic_string< _Elem >::_ThisX strX(str.c_str());
    std::cout << "   To _ElemX :                        ";
    showhex(strX);

    typename basic_string< _Elem >::_ThisY strY(str.c_str());
    std::cout << "   To _ElemY :                        ";
    showhex(strY);
}

template< typename _Elem >
void testAssignment(const basic_string< _Elem > & str)
{
    std::cout << "== Assignment test" << std::endl;

    typename basic_string< _Elem >::_ThisX strX;
    strX = str;
    std::cout << "   To _ElemX :                        ";
    showhex(strX);

    typename basic_string< _Elem >::_ThisY strY;
    strY = str;
    std::cout << "   To _ElemY :                        ";
    showhex(strY);
}

template< typename _Elem >
void testExplicit(const basic_string< _Elem > & str)
{
    std::cout << "== Explicit test" << std::endl;

    std::cout << "   ToY :                              ";
    showhex(str.toY());

    typename basic_string< _Elem >::_ThisY strY;
    std::cout << "   FromY :                            ";
    showhex(strY.fromY(str.c_str()));
}

template< typename _Elem >
void testUtf8(const basic_string< _Elem > & str)
{
    std::cout << "== UTF-8 test" << std::endl;

    std::string strUtf8 = str.toutf8();
    std::cout << "   To UTF-8 :                         ";
    showhex(strUtf8);

    typename basic_string< _Elem >::_ThisX strX;
    std::cout << "   _ElemX from UTF-8 (fromutf8 call): ";
    showhex(strX.fromutf8(strUtf8));
    std::cout << "   _ElemX from UTF-8 (assign   call): ";
    showhex(strX = strUtf8);

    typename basic_string< _Elem >::_ThisY strY;
    std::cout << "   _ElemY from UTF-8 (Explicit call): ";
    showhex(strY.fromutf8(strUtf8));
    std::cout << "   _ElemY from UTF-8 (assign   call): ";
    showhex(strY = strUtf8);
}

template< typename _Elem >
void testFormat(const basic_string< _Elem > & str)
{
    std::cout << "== Format test" << std::endl;

    typename basic_string< _Elem >::_ThisX strFormat("%s");

    typename basic_string< _Elem >::_ThisX strX;
    strX.format(strFormat.c_str(), str.c_str());
    std::cout << "   _ElemX format :                    ";
    showhex(strX);

    typename basic_string< _Elem >::_ThisY strY;
    strY.format(strFormat.c_str(), str.c_str());
    std::cout << "   _ElemY format :                    ";
    showhex(strY);
}

template< typename _Elem >
void test(const basic_string< _Elem > & str)
{
    std::cout << "From : ";		showhex(str);

    testConstructor(str);
    testAssignment(str);
    testExplicit(str);
    testUtf8(str);
    testFormat(str);
}

template< typename _Elem >
void testReplaceString(basic_string< _Elem > & str)
{
    std::cout << "From : " << string(str) << std::endl;

    str.replace("string", "ANSI to ANSI");
    std::cout << "ANSI to ANSI : " << string(str) << std::endl;

    str.replace("ANSI to ANSI", L"ANSI to UNICODE");
    std::cout << "ANSI to UNICODE : " << string(str) << std::endl;

    str.replace(L"ANSI to UNICODE", "UNICODE to ANSI");
    std::cout << "UNICODE to ANSI : " << string(str) << std::endl;

    str.replace(L"UNICODE to ANSI", L"UNICODE to UNICODE");
    std::cout << "UNICODE to UNICODE : " << string(str) << std::endl;
}

template< typename _Elem >
void testTolowerandToupper(basic_string< _Elem > & str)
{
    std::cout << "From : " << string(str) << std::endl;

    std::cout << "ToLower : " << string(basic_string< _Elem >(str).tolower()) << std::endl;
    std::cout << "ToUpper : " << string(basic_string< _Elem >(str).toupper()) << std::endl;
}

int main()
{
#ifndef __AVOID_STL4017__
    //setlocale(LC_ALL, "ko-KR");		// You should set locale information.
    setlocale(LC_ALL, "");
#endif

    {
        // Sample text - Korean

        wchar_t szString[4] = { (wchar_t)0xBB38, (wchar_t)0xC790, (wchar_t)0xC5F4, (wchar_t)0x0000 };

        string strBaseANSI(szString);
        std::cout << "==== Test from ANSI string ====" << std::endl;
        test(strBaseANSI);
        std::cout << "===============================" << "\n\n";

        wstring strBaseUNICODE(szString);
        std::cout << "==== Test from UNCIDOE string ====" << std::endl;
        test(strBaseUNICODE);
        std::cout << "==================================" << "\n\n";

        string strBasUtf8(strBaseUNICODE.toutf8());
        std::cout << "==== Test from UTF-8 string ====" << std::endl;
        test(strBasUtf8);
        std::cout << "==================================" << "\n\n";
    }

    {
        string strANSI("ANSI [string]");
        wstring strUNICODE(L"UNICODE [string]");

        std::cout << "==== Replace from ANSI string ====" << std::endl;
        testReplaceString(strANSI);
        std::cout << "==================================" << "\n\n";

        std::cout << "==== Replace from UNCIDOE string ====" << std::endl;
        testReplaceString(strUNICODE);
        std::cout << "=====================================" << "\n\n";
    }

    {
        string strANSI("ANSI TeST StriNg");
        string strUNICODE("UNICODE TeST StriNg");

        std::cout << "==== to lower and to upper from ANSI string ====" << std::endl;
        testTolowerandToupper(strANSI);
        std::cout << "================================================" << "\n\n";

        std::cout << "==== to lower and to upper from UNICODE string ====" << std::endl;
        testTolowerandToupper(strUNICODE);
        std::cout << "===================================================" << "\n\n";
    }

    //basic_string< int > strInt;

    return 0;
}
