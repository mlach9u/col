#ifndef __INCLUSION_COL_BASE_H__
#define __INCLUSION_COL_BASE_H__

#ifdef _MSC_VER
#if _MSC_VER < 1600							// [..., VS2010)
#define __COL_CONSTEXPR__			0
#define __COL_ALIAS_TEMPLATES__		0
#elif _MSC_VER < 1700						// [VS2010, VS2012)
#define __COL_CONSTEXPR__			0
#define __COL_ALIAS_TEMPLATES__		0
#elif _MSC_VER < 1800						// [VS2012, VS2013)
#define __COL_CONSTEXPR__			0
#define __COL_ALIAS_TEMPLATES__		0
#elif _MSC_VER < 1900						// [VS2013, VS2015)
#define __COL_CONSTEXPR__			0
#define __COL_ALIAS_TEMPLATES__		1
#else										// [VS2015, ...)
#define __COL_CONSTEXPR__			1
#define __COL_ALIAS_TEMPLATES__		1
#endif
#else										// !Visual Studio
#define __COL_CONSTEXPR__			1
#define __COL_ALIAS_TEMPLATES__		1
#endif

#endif
