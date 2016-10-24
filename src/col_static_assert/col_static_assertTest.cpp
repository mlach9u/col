#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>
#include "col_static_assert.h"

static_assert(true, "Error1");
static_assert(3 < 2, "Error2");
static_assert(1 == 1, "Error3");
static_assert(false, "Error4");
static_assert(0, "Error5");

int main(int argc, char* argv[])
{
	return 0;
}
