#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>
#include "col_base.h"

#define COUNTER_STRING(a) COL_STRING(COL_GLUE(a, __COUNTER__))

int main(int argc, char* argv[])
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
