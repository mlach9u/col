#ifndef __INCLUSION_STRINGT_H__
#define __INCLUSION_STRINGT_H__

#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <string>

#ifdef _MSC_VER
#if _MSC_VER < 1600							// [..., VS2010)
#define __STRINGT_INCLUSION_CODECVT__	0
#define __STRINGT_INCLUSION_WINDOWS_H__ 1
#else										// [VS2010, ...)
#define __STRINGT_INCLUSION_CODECVT__	1
#define __STRINGT_INCLUSION_WINDOWS_H__ 0
#endif
#else										// !Visual Studio
#define __STRINGT_INCLUSION_CODECVT__	1
#define __STRINGT_INCLUSION_WINDOWS_H__ 0
#endif

#if __STRINGT_INCLUSION_CODECVT__
#include <codecvt>
#endif

#if __STRINGT_INCLUSION_WINDOWS_H__
#include <Windows.h>
#endif

#endif
