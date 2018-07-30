#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

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
		std::map< std::string, std::vector< std::string > > data;

		{
			std::vector< std::string > vps;
			vps.push_back((std::string("1_1")));
			vps.push_back((std::string("1_2")));
			vps.push_back((std::string("1_3")));
			vps.push_back((std::string("1_4")));
			vps.push_back((std::string("1_5")));
			data[std::string("vps1")] = vps;
		}

		{
			std::vector< std::string > vps;
			vps.push_back((std::string("2_1")));
			vps.push_back((std::string("2_2")));
			vps.push_back((std::string("2_3")));
			vps.push_back((std::string("2_4")));
			vps.push_back((std::string("2_5")));
			data[std::string("vps2")] = vps;
		}

		{
			std::vector< std::string > vps;
			vps.push_back((std::string("3_1")));
			vps.push_back((std::string("3_2")));
			vps.push_back((std::string("3_3")));
			vps.push_back((std::string("3_4")));
			vps.push_back((std::string("3_5")));
			data[std::string("vps3")] = vps;
		}

		{
			std::vector< std::string > vps;
			vps.push_back((std::string("4_1")));
			vps.push_back((std::string("4_2")));
			vps.push_back((std::string("4_3")));
			vps.push_back((std::string("4_4")));
			vps.push_back((std::string("4_5")));
			data[std::string("vps4")] = vps;
		}

		write(std::string("filename.ext"), data);
	}

	{
		std::map< std::string, std::vector< std::string > > data;
		read(std::string("filename.ext"), data);
		write(std::string("filename2.ext"), data);
	}

	return 0;
}
