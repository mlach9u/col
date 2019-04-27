#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "debugout.h"

int main(int argc, char* argv[])
{
    dstream dout;

    dout << "Debug string test" << std::endl;

    dout << "argc : " << argc << std::endl;
    for (int i = 0; i < argc; i++)
        dout << "argv[" << i << "] = " << argv[i] << std::endl;

    return 0;
}
