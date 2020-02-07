#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>
#include <string>
#include <algorithm>
#include "funct.h"

int main()
{
    std::string str("tEsT stRINg");

    std::cout << "To lower string : " << str << " -> ";
    std::for_each(str.begin(), str.end(),
        condition_operator(
            range(std::greater_equal< char >(), 'A', std::less_equal< char >(), 'Z'),
            std::bind2nd(
                complex_assignment(std::plus< char >()),
                (char)('a' - 'A')
            )
        )
    );
    std::cout << str << std::endl;

    str = "TeST StrInG";

    std::cout << "To upper string : " << str << " -> ";
    std::for_each(str.begin(), str.end(),
        condition_operator(
            range(std::greater_equal< char >(), 'a', std::less_equal< char >(), 'z'),
            std::bind2nd(
                complex_assignment(std::minus< char >()),
                (char)('a' - 'A')
            )
        )
    );
    std::cout << str << std::endl;

    return 0;
}
