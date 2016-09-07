#ifndef __INCLUSION_STRINGT_H__
#define __INCLUSION_STRINGT_H__

#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <string>

#define UTF8_CONVERTER_TYPE_CODECVT		1	// use std::wstring_convert< std::codecvt_utf8< wchar_t > >
#define UTF8_CONVERTER_TYPE_WINAPI		2	// use WideCharToMultiByte and MultiByteToWideChar functions

#ifndef UTF8_CONVERTER_TYPE
#ifdef _MSC_VER
#if _MSC_VER >= 1600		// Visual Studio 2010
#define UTF8_CONVERTER_TYPE UTF8_CONVERTER_TYPE_CODECVT
#elif _WINDOWS_
#define UTF8_CONVERTER_TYPE UTF8_CONVERTER_TYPE_WINAPI
#endif
#else
#define UTF8_CONVERTER_TYPE UTF8_CONVERTER_TYPE_CODECVT
#endif
#endif

#if (UTF8_CONVERTER_TYPE == UTF8_CONVERTER_TYPE_CODECVT)
#include <codecvt>
#elif (UTF8_CONVERTER_TYPE == UTF8_CONVERTER_TYPE_WINAPI)
#include <Windows.h>
#endif

#endif
