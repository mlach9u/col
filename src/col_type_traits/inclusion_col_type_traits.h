#ifndef __INCLUSION_COL_TYPE_TRAITS_H__
#define __INCLUSION_COL_TYPE_TRAITS_H__

#include "..\\col_base\\col_base.h"

#ifdef _MSC_VER

#if _MSC_VER < 1600							// [..., VS2010)

#ifndef __COL_INCLUSION_TYPE_TRAITS__
#define __COL_INCLUSION_TYPE_TRAITS__	1
#endif

#ifndef __COL_USE_TR1_NAMESPACE__
#define __COL_USE_TR1_NAMESPACE__		1
#endif

#else										// [VS2010, ...)

#ifndef __COL_INCLUSION_TYPE_TRAITS__
#define __COL_INCLUSION_TYPE_TRAITS__	1
#endif

#ifndef __COL_USE_TR1_NAMESPACE__
#define __COL_USE_TR1_NAMESPACE__		0
#endif

#endif

#else										// !Visual Studio

#ifndef __COL_INCLUSION_TYPE_TRAITS__
#define __COL_INCLUSION_TYPE_TRAITS__	1
#endif

#ifndef __COL_USE_TR1_NAMESPACE__
#define __COL_USE_TR1_NAMESPACE__		0
#endif

#endif

#if __COL_INCLUSION_TYPE_TRAITS__
#include <type_traits>
#endif

#endif
