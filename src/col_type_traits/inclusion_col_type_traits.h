#ifndef __INCLUSION_COL_TYPE_TRAITS_H__
#define __INCLUSION_COL_TYPE_TRAITS_H__

#include "..\\col_base\\inclusion_col_base.h"

#ifdef _MSC_VER
#if _MSC_VER < 1600							// [..., VS2010)
#define __COL_INCLUSION_TYPE_TRAITS__	0
#else										// [VS2010, ...)
#define __COL_INCLUSION_TYPE_TRAITS__	1
#endif
#else										// !Visual Studio
#define __COL_INCLUSION_TYPE_TRAITS__	1
#endif

#if __COL_INCLUSION_TYPE_TRAITS__
#include <type_traits>
#endif

#endif
