#ifndef __INCLUSION_COL_STATIC_ASSERT_H__
#define __INCLUSION_COL_STATIC_ASSERT_H__

#include "..\\col_base\\inclusion_col_base.h"

#ifdef _MSC_VER
#if _MSC_VER < 1600							// [..., VS2010)
#define __COL_DEFINE_STATIC_ASSERT__	1
#else										// [VS2010, ...)
#define __COL_DEFINE_STATIC_ASSERT__	0
#endif
#else										// !Visual Studio
#define __COL_DEFINE_STATIC_ASSERT__	0
#endif

#endif
