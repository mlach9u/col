#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>
#include "tvalue.h"

struct date
{
    short year;
    short month;
    short day;
};

template< typename _Elem, typename _Traits >
std::basic_ostream< _Elem, _Traits >& operator << (std::basic_ostream< _Elem, _Traits >& _Ostr, const date& _Pd)
{
    _Ostr << _Pd.year << "-" << _Pd.month << "-" << _Pd.day;
    return _Ostr;
}

template< typename _Ty >
void print(_Ty t)
{
    std::cout << typeid(_Ty).name() << " : " << t << std::endl;
}

int main(int argc, char* argv[])
{
    try
    {
        tvalue v;
        v = 100.5;
        print<float>(v);
        print<const long&>(v);

        v = 50;
        print<const double&>(v);
        print<short>(v);

        v = 30;

        date pd;
        pd.year = 2018;
        pd.month = 8;
        pd.day = 13;

        v = pd;
        print<date>(v);
        print<const date&>(v);

        v = "hello";
        print<const char*>(v);
        print<std::string>(v);
        print<const std::string&>(v);
    }
    catch (std::exception & e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
