#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>
#include "col_type_traits.h"

#define PRINT_IS_CHAR(t) COL_STRING(t) << " = " << (is_char< t >::value ? "true" : "false")

int main()
{
    std::cout << PRINT_IS_CHAR(char) << std::endl;
    std::cout << PRINT_IS_CHAR(wchar_t) << std::endl;
#if __COL_CHAR16_T__
    std::cout << PRINT_IS_CHAR(char16_t) << std::endl;
#endif
#if __COL_CHAR32_T__
    std::cout << PRINT_IS_CHAR(char32_t) << std::endl;
#endif
    std::cout << PRINT_IS_CHAR(int) << std::endl;
    std::cout << PRINT_IS_CHAR(long) << std::endl;
    return 0;
}
