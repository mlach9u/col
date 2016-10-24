#ifndef __COL_STATIC_ASSERT_H__
#define __COL_STATIC_ASSERT_H__

#include "inclusion_col_static_assert.h"
#include "..\\col_base\\col_base.h"

#if __COL_DEFINE_STATIC_ASSERT__
template< bool b > struct __col_static_assert_test {};
template<> struct __col_static_assert_test< false >;
template< int n > struct __col_static_assert_base {};
#define __col_static_assert(exp, msg, count)\
	typedef __col_static_assert_base<\
		sizeof(__col_static_assert_test< exp >)\
	> COL_GLUE(__col_static_assert_type, count)
#define static_assert(exp, msg) __col_static_assert(exp, msg, __COUNTER__)
#endif

#endif
