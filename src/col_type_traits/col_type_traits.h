#ifndef __COL_TYPE_TRAITS_H__
#define __COL_TYPE_TRAITS_H__

#include "inclusion_col_type_traits.h"

#ifdef _TYPE_TRAITS_

#if __COL_USE_TR1_NAMESPACE__
#define __COL_NS__		::std::tr1::
#else
#define __COL_NS__		::std::
#endif

using __COL_NS__ add_const;
using __COL_NS__ add_cv;
using __COL_NS__ add_pointer;
using __COL_NS__ add_volatile;
using __COL_NS__ aligned_storage;
using __COL_NS__ alignment_of;
//using __COL_NS__ conditional;
//using __COL_NS__ decay;
using __COL_NS__ enable_if;
using __COL_NS__ extent;
using __COL_NS__ false_type;
using __COL_NS__ has_virtual_destructor;
using __COL_NS__ integral_constant;
using __COL_NS__ is_abstract;
using __COL_NS__ is_arithmetic;
using __COL_NS__ is_array;
using __COL_NS__ is_base_of;
using __COL_NS__ is_class;
using __COL_NS__ is_compound;
using __COL_NS__ is_const;
using __COL_NS__ is_convertible;
using __COL_NS__ is_empty;
using __COL_NS__ is_enum;
using __COL_NS__ is_floating_point;
using __COL_NS__ is_function;
using __COL_NS__ is_fundamental;
using __COL_NS__ is_integral;
using __COL_NS__ is_member_function_pointer;
using __COL_NS__ is_member_object_pointer;
using __COL_NS__ is_member_pointer;
using __COL_NS__ is_object;
using __COL_NS__ is_pod;
using __COL_NS__ is_pointer;
using __COL_NS__ is_polymorphic;
using __COL_NS__ is_reference;
using __COL_NS__ is_same;
using __COL_NS__ is_scalar;
using __COL_NS__ is_signed;
using __COL_NS__ is_union;
using __COL_NS__ is_unsigned;
using __COL_NS__ is_void;
using __COL_NS__ is_volatile;
//using __COL_NS__ make_signed;
//using __COL_NS__ make_unsigned;
using __COL_NS__ rank;
using __COL_NS__ remove_all_extents;
using __COL_NS__ remove_const;
using __COL_NS__ remove_cv;
using __COL_NS__ remove_extent;
using __COL_NS__ remove_pointer;
using __COL_NS__ remove_reference;
using __COL_NS__ remove_volatile;
using __COL_NS__ true_type;

#undef __COL_NS__

#else

#error "Type traits is not included."

#endif

#if __COL_ALIAS_TEMPLATES__
template<bool b>
using bool_constant = integral_constant< bool, b >;
#else
template<bool b>
struct bool_constant : integral_constant< bool, b > {};
#endif

template<typename _Ty, _Ty _First, _Ty _Second>
struct integral_pair
{
    typedef _Ty value_type;
    typedef integral_pair<_Ty, _First, _Second> type;

    typedef integral_constant<_Ty, _First> first_type;
    typedef integral_constant<_Ty, _Second> second_type;

    typedef typename first_type::value_type first_value_type;
    typedef typename second_type::value_type second_value_type;

    static first_value_type first_value() { return first_type::value; }
    static second_value_type second_value() { return second_type::value; }
};

template<typename _Ty, _Ty _Val1, _Ty _Val2>
struct is_same_value : false_type {};

template<typename _Ty, _Ty _Val>
struct is_same_value<_Ty, _Val, _Val> : true_type {};

template<typename _Ty> struct col_is_char : false_type {};
template<> struct col_is_char<char> : true_type {};
template<> struct col_is_char<wchar_t> : true_type {};
#if __COL_CHAR16_T__
template<> struct col_is_char<char16_t> : true_type {};
#endif
#if __COL_CHAR32_T__
template<> struct col_is_char<char32_t> : true_type {};
#endif

template<typename _Ty>
struct is_char : col_is_char<typename remove_cv<_Ty>::type> {};

#if __COL_ALIAS_TEMPLATES__ && __COL_CONSTEXPR__
template<typename _Ty>
constexpr bool is_char_v = is_char<_Ty>::value;
#endif

template<typename _Ty> struct col_is_default : false_type {};
template<> struct col_is_default<bool> : true_type {};
template<> struct col_is_default<char> : true_type {};
template<> struct col_is_default<unsigned char> : true_type {};
template<> struct col_is_default<wchar_t> : true_type {};
template<> struct col_is_default<short> : true_type {};
template<> struct col_is_default<unsigned short> : true_type {};
template<> struct col_is_default<int> : true_type {};
template<> struct col_is_default<unsigned int> : true_type {};
template<> struct col_is_default<long> : true_type {};
template<> struct col_is_default<unsigned long> : true_type {};
template<> struct col_is_default<long long> : true_type {};
template<> struct col_is_default<unsigned long long> : true_type {};
template<> struct col_is_default<float> : true_type {};
template<> struct col_is_default<double> : true_type {};
template<> struct col_is_default<long double> : true_type {};

template<typename _Ty>
struct is_default : col_is_default<typename remove_cv<_Ty>::type> {};

#if __COL_ALIAS_TEMPLATES__ && __COL_CONSTEXPR__
template<typename _Ty>
constexpr bool is_default_v = is_default<_Ty>::value;
#endif

#endif
