
## Type traits

---
<https://github.com/mlach9u/col/tree/master/src/col_type_traits>

### 목적

메타 프로그래밍의 기반이 되는 `type_traits` 구조를 확장하였으며 아래와 같은 내용이 포함됩니다.

1. 각 Visual Studio 버전 별 `type_traits` 헤더 통합
2. 새로운 type traits에 대한 정의문

### Visual Studio 버전별 `type_traits` 헤더 통합

Visual Studio 버전별로 type_traits 헤더를 사용하는 방법이 다릅니다. 예를 들어, `std::is_same`을 사용한다고 가정한다면,

1. Visual Studio 2008에서는 `std::tr1::is_same`을 사용해야 하고
2. Visual Studio 2015에서는 `std::is_same`을 사용합니다.

이 프로젝트를 포함하면 아래 문법을 사용하여 `type_traits`를 현재 namespace에 선언합니다.

```cpp
#if __COL_USE_TR1_NAMESPACE__
#define __COL_NS__		::std::tr1::
#else
#define __COL_NS__		::std::
#endif

using __COL_NS__ add_const;
using __COL_NS__ add_cv;
using __COL_NS__ add_pointer;
...
```

### 새로운 type traits 정의

*`integral_pair` 정의*

`integral_constant`와 비슷하지만 아래와 같이 두 개의 값을 가질 수 있는 `integral_pair`를 새로 정의하였습니다.

```cpp
template< typename _Ty, _Ty _First, _Ty _Second >
struct integral_pair
{
	typedef _Ty value_type;
	typedef integral_pair< _Ty, _First, _Second > type;

	typedef integral_constant< _Ty, _First > first_type;
	typedef integral_constant< _Ty, _Second > second_type;

	typedef typename first_type::value_type first_value_type;
	typedef typename second_type::value_type second_value_type;

	static first_value_type first_value() { return first_type::value; }
	static second_value_type second_value() { return second_type::value; }
};
```

*`is_same_value` 정의*

두 개의 템플릿 인수값이 동일한지 판단할 수 있으며, 아래와 같이 구현됩니다.

```cpp
template< typename _Ty, _Ty _Val1, _Ty _Val2 >
struct is_same_value : false_type {};

template< typename _Ty, _Ty _Val >
struct is_same_value< _Ty, _Val, _Val > : true_type {};
```

*`is_char` 정의*

전달된 템플릿 형식이 문자 형식인지 판단할 수 있으며, 아래와 같이 구현됩니다.

```cpp
template< typename _Ty > struct col_is_char : false_type {};
template<> struct col_is_char< char > : true_type {};
template<> struct col_is_char< wchar_t > : true_type {};
#if __COL_CHAR16_T__
template<> struct col_is_char< char16_t > : true_type {};
#endif
#if __COL_CHAR32_T__
template<> struct col_is_char< char32_t > : true_type {};
#endif

template< typename _Ty >
struct is_char : col_is_char< typename remove_cv< _Ty >::type > {};

#if __COL_ALIAS_TEMPLATES__ && __COL_CONSTEXPR__
template< typename _Ty >
constexpr bool is_char_v = is_char< _Ty >::value;
#endif
```
