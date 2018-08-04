#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <string>
#include <vector>
#include <list>
#include <map>
#include <tuple>

#include <fstream>
#include "bstream_operator.h"

int __col_stream_index__ = std::ios_base::xalloc();

template< typename _Elem, typename _Ty >
void write(const std::basic_string< _Elem >& _Name, const _Ty& _Data)
{
	std::basic_ofstream< _Elem > ofs(_Name);
	basic_bostream< _Elem > bos(ofs.rdbuf());
	bos << _Data;
}

template< typename _Elem, typename _Ty >
void read(const std::basic_string< _Elem >& _Name, _Ty& _Data)
{
	std::basic_ifstream< _Elem > ifs(_Name);
	basic_bistream< _Elem > bis(ifs.rdbuf());
	bis >> _Data;
}

int main(int argc, char* argv[])
{
	{
		std::tuple< int, double, std::string,
			std::vector< float >,
			std::list< std::pair< int, double > >,
			std::map< std::string, std::string >
		> data;

		write(std::string("filename.ext"), data);
	}

	{
		std::tuple< int, double, std::string,
			std::vector< float >,
			std::list< std::pair< int, double > >,
			std::map< std::string, std::string >
		> data;

		read(std::string("filename.ext"), data);
	}

	return 0;
}
