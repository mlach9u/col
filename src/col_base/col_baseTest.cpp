#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>
#include "col_base.h"

static_assert(true, "This is not error.");
//static_assert(false, "Expression must be true.");
static_assert(3 == 3, "This is not error.");
//static_assert(5 < 0, "5 must be positive number.");

#define COUNTER_STRING(a) COL_STRING(COL_GLUE(a, __COUNTER__))

int main()
{
    std::cout << COUNTER_STRING(count_) << std::endl;
    std::cout << COUNTER_STRING(count_) << std::endl;
    std::cout << COUNTER_STRING(count_) << std::endl;
    std::cout << COUNTER_STRING(count_) << std::endl;
    std::cout << COUNTER_STRING(count_) << std::endl;
    std::cout << COUNTER_STRING(count_) << std::endl;
    std::cout << COUNTER_STRING(count_) << std::endl;
    std::cout << COUNTER_STRING(count_) << std::endl;
    std::cout << COUNTER_STRING(count_) << std::endl;
    std::cout << COUNTER_STRING(count_) << std::endl;
    std::cout << COUNTER_STRING(count_) << std::endl;
    return 0;
}
