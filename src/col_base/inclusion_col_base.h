#ifndef __INCLUSION_COL_BASE_H__
#define __INCLUSION_COL_BASE_H__

#ifdef _MSC_VER

#if _MSC_VER < 1600							// [..., VS2010)

#ifndef __COL_CONSTEXPR__
#define __COL_CONSTEXPR__			0
#endif

#ifndef __COL_ALIAS_TEMPLATES__
#define __COL_ALIAS_TEMPLATES__		0
#endif

#ifndef __COL_STATIC_ASSERT__
#define __COL_STATIC_ASSERT__		0
#endif

#ifndef __COL_CHAR16_T__
#define __COL_CHAR16_T__			0
#endif

#ifndef __COL_CHAR32_T__
#define __COL_CHAR32_T__			0
#endif

#ifndef __COL_VARIADIC_TEMPLATES__
#define __COL_VARIADIC_TEMPLATES__	0
#endif

#elif _MSC_VER < 1700						// [VS2010, VS2012)

#ifndef __COL_CONSTEXPR__
#define __COL_CONSTEXPR__			0
#endif

#ifndef __COL_ALIAS_TEMPLATES__
#define __COL_ALIAS_TEMPLATES__		0
#endif

#ifndef __COL_STATIC_ASSERT__
#define __COL_STATIC_ASSERT__		1
#endif

#ifndef __COL_CHAR16_T__
#define __COL_CHAR16_T__			0
#endif

#ifndef __COL_CHAR32_T__
#define __COL_CHAR32_T__			0
#endif

#ifndef __COL_VARIADIC_TEMPLATES__
#define __COL_VARIADIC_TEMPLATES__	0
#endif

#elif _MSC_VER < 1800						// [VS2012, VS2013)

#ifndef __COL_CONSTEXPR__
#define __COL_CONSTEXPR__			0
#endif

#ifndef __COL_ALIAS_TEMPLATES__
#define __COL_ALIAS_TEMPLATES__		0
#endif

#ifndef __COL_STATIC_ASSERT__
#define __COL_STATIC_ASSERT__		1
#endif

#ifndef __COL_CHAR16_T__
#define __COL_CHAR16_T__			0
#endif

#ifndef __COL_CHAR32_T__
#define __COL_CHAR32_T__			0
#endif

#ifndef __COL_VARIADIC_TEMPLATES__
#define __COL_VARIADIC_TEMPLATES__	0
#endif

#elif _MSC_VER < 1900						// [VS2013, VS2015)

#ifndef __COL_CONSTEXPR__
#define __COL_CONSTEXPR__			0
#endif

#ifndef __COL_ALIAS_TEMPLATES__
#define __COL_ALIAS_TEMPLATES__		1
#endif

#ifndef __COL_STATIC_ASSERT__
#define __COL_STATIC_ASSERT__		1
#endif

#ifndef __COL_CHAR16_T__
#define __COL_CHAR16_T__			0
#endif

#ifndef __COL_CHAR32_T__
#define __COL_CHAR32_T__			0
#endif

#ifndef __COL_VARIADIC_TEMPLATES__
#define __COL_VARIADIC_TEMPLATES__	1
#endif

#else										// [VS2015, ...)

#ifndef __COL_CONSTEXPR__
#define __COL_CONSTEXPR__			1
#endif

#ifndef __COL_ALIAS_TEMPLATES__
#define __COL_ALIAS_TEMPLATES__		1
#endif

#ifndef __COL_STATIC_ASSERT__
#define __COL_STATIC_ASSERT__		1
#endif

#ifndef __COL_CHAR16_T__
#define __COL_CHAR16_T__			1
#endif

#ifndef __COL_CHAR32_T__
#define __COL_CHAR32_T__			1
#endif

#ifndef __COL_VARIADIC_TEMPLATES__
#define __COL_VARIADIC_TEMPLATES__	1
#endif

#endif

#else										// !Visual Studio

#ifndef __COL_CONSTEXPR__
#define __COL_CONSTEXPR__			1
#endif

#ifndef __COL_ALIAS_TEMPLATES__
#define __COL_ALIAS_TEMPLATES__		1
#endif

#ifndef __COL_STATIC_ASSERT__
#define __COL_STATIC_ASSERT__		1
#endif

#ifndef __COL_CHAR16_T__
#define __COL_CHAR16_T__			1
#endif

#ifndef __COL_CHAR32_T__
#define __COL_CHAR32_T__			1
#endif

#ifndef __COL_VARIADIC_TEMPLATES__
#define __COL_VARIADIC_TEMPLATES__	1
#endif

#endif

#endif
