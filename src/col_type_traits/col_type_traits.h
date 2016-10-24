#ifndef __COL_TYPE_TRAITS_H__
#define __COL_TYPE_TRAITS_H__

#include "inclusion_col_type_traits.h"
#include "..\\col_base\\col_base.h"

#ifdef _TYPE_TRAITS_
#if __COL_ALIAS_TEMPLATES__
template< typename _Ty, _Ty v >
using col_integral_constant = std::integral_constant< _Ty, v >;
#else
template< typename _Ty, _Ty v >
struct col_integral_constant
	: public std::integral_constant< _Ty, v >
{};
#endif
#else
template< typename _Ty, _Ty v >
struct col_integral_constant
{
	static const _Ty value = v;

	typedef _Ty value_type;
	typedef col_integral_constant< _Ty, v > type;
};
typedef col_integral_constant< bool, true > col_true_type;
typedef col_integral_constant< bool, false > col_false_type;
#endif

#endif
