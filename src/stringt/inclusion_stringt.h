#ifndef __INCLUSION_STRINGT_H__
#define __INCLUSION_STRINGT_H__

#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <cstring>

#include <algorithm>

#include <cctype>
#include <cwctype>

#ifdef _MSC_VER

#ifndef __STRINGT_INCLUSION_CODECVT__
#define __STRINGT_INCLUSION_CODECVT__	0
#endif

#ifndef __STRINGT_INCLUSION_WINDOWS_H__
#define __STRINGT_INCLUSION_WINDOWS_H__ 1
#endif

#else

#ifndef __STRINGT_INCLUSION_CODECVT__
#define __STRINGT_INCLUSION_CODECVT__	1
#endif

#ifndef __STRINGT_INCLUSION_WINDOWS_H__
#define __STRINGT_INCLUSION_WINDOWS_H__ 0
#endif

#endif

#if __STRINGT_INCLUSION_CODECVT__
#ifdef __linux__
#define _CODECVT_
#endif
#include <locale>
#include <codecvt>
#endif

#if __STRINGT_INCLUSION_WINDOWS_H__
#include <Windows.h>
#endif

#include "../col_base/col_base.h"
#include "../col_type_traits/inclusion_col_type_traits.h"

#endif
