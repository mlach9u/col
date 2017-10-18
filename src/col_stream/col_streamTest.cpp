#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <fstream>
#include "bstream.h"

int __col_stream_index__ = std::ios_base::xalloc();

int main(int argc, char* argv[])
{
	bool b = false;
	short s = 1;
	unsigned short us = 2;
	int i = 3;
	unsigned int ui = 4;
	long l = 5;
	unsigned long ul = 6;
	long long ll = 7;
	unsigned long long ull = 8;
	float f = 9.0;
	double d = 10.0;
	long double ld = 11.0;
	char c = 0x30;
	unsigned char uc = 0x31;
	wchar_t wc = 0x32;

	std::cout << bins << (int)0x30313233 << nobins << std::endl;

	{
		std::ofstream ofs("test.dat");
		bostream f_bos(ofs.rdbuf());
		f_bos << b << s << us << i << ui << l << ul << ll << ull << f << d << ld << c << uc << wc;
	}

	{
		std::ifstream ifs("test.dat");
		bistream f_bis(ifs.rdbuf());
		f_bis >> b >> s >> us >> i >> ui >> l >> ul >> ll >> ull >> f >> d >> ld >> c >> uc >> wc;
	}

	binarybuf bb;

	{
		bostream bos(&bb);
		bos << b << s << us << i << ui << l << ul << ll << ull << f << d << ld << c << uc << wc;
	}

	const char* p = bb.ptr();
	int cb = bb.size();

	std::cout << std::hex;
	for (int _i = 0; _i < cb; _i++)
		std::cout << (int)p[_i] << ' ';
	std::cout << std::dec << std::endl;

	{
		bistream bis(&bb);
		bis >> b >> s >> us >> i >> ui >> l >> ul >> ll >> ull >> f >> d >> ld >> c >> uc >> wc;
	}

	return 0;
}
