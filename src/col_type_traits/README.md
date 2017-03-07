##Type traits(`col_type_traits.h`)

---

###Purpose

1. Adapter of `type_traits` header.
2. Define several new type traits.

###Adapter of `type_traits` header.

For example, to use `is_same` struct:

1. `std::tr1::is_same` with VS2008.
2. `std::is_same` with VS2015.

This header adapt to current namespace.

###Define several new type traits

####`integral_pair` wraps two static constants of specified type.

>```cpp
>template< typename _Elem, _Elem _First, _Elem _Second >
>struct integral_pair;
>```

####Trait class that identifies whether _Ty_ is a char type(`is_char`)

- `char`
- `wchar_t`
- `char16_t`
- `char32_t`
