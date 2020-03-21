#ifndef __COL_BASE_H__
#define __COL_BASE_H__

#include "inclusion_col_base.h"

#define COL_GLUE2(a, b) a##b
#define COL_GLUE1(a, b) COL_GLUE2(a, b)
#define COL_GLUE(a, b) COL_GLUE1(a, b)

#define COL_STRING2(a) #a
#define COL_STRING1(a) COL_STRING2(a)
#define COL_STRING(a) COL_STRING1(a)

#if !__COL_STATIC_ASSERT__
template< bool b > struct __col_static_assert_test {};
template<> struct __col_static_assert_test< false >;
template< int n > struct __col_static_assert_base {};
#define __col_static_assert(exp, msg, count)\
    typedef __col_static_assert_base<\
        sizeof(__col_static_assert_test< exp >)\
    > COL_GLUE(__col_static_assert_type, count)
#define static_assert(exp, msg) __col_static_assert(exp, msg, __COUNTER__)
#endif

#define COL_UNREFERENCE_PARAMETER(p)    (p)

#ifdef _WIN32
#ifndef CDECL
#define CDECL __cdecl
#endif
#elif __linux__
#define CDECL
#endif

#endif
