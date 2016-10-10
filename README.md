
#Collection of libraries.

##Notice

> These are in global namespace. To declare in other namespace, following this:

>1. Include `inclusion_xxx.h` file in global namespace.
>2. Include the main file in available namespace.

> For example,

>```cpp
#include "src\\stringt\\inclusion_stringt.h"
namespace something
{
#include "src\\stringt\\stringt.h"
}
>```

##License

> These are in the Public Domain.



---

##basic_string(src\stringt\stringt.h)

###Concept

1. This is template class extended from `std::basic_string`.
2. This is designed for convert between ASCII and UNICODE and UTF-8.

###Notice

`basic_string` template class has two element types: `_ElemX` and `_ElemY`. `_ElemX` is template argument. Another is `_ElemY`.

>```cpp
basic_string< char >::_ElemX // is char
basic_string< char >::_ElemY // is wchar_t
basic_string< wchar_t >::_ElemX // is wchar_t
basic_string< wchar_t >::_ElemY // is char
>```

Similarly:

>```cpp
basic_string< ... >::_StrX // is std::basic_string< _ElemX >
basic_string< ... >::_StrY // is std::basic_string< _ElemY >
basic_string< ... >::_ThisX // is basic_string< _ElemX >
basic_string< ... >::_ThisY // is basic_string< _ElemY >
>```

Some functions in `basic_string` template class are influenced by locale information. If you want detail information, visit [setlocale](http://www.cplusplus.com/reference/clocale/setlocale/).

###Usage

####Convert between ASCII and UNICODE

#####Use constructor
>```cpp
basic_string< char > strANSI(L"Hello World!");
>```

#####Use assignment
>```cpp
basic_string< wchar_t > strUNICODE;
strUNICODE = "Hello World!";
>```

#####Explicit converting
>```cpp
basic_string< char > strANSI;
strANSI.fromY(L"Hello World!");
strANSI.toY();
>```

####Formatting

#####From `_ElemX`

>```cpp
int nResult = 0;
basic_string< char > strANSI;
strANSI.format("Result is %d", nResult);
>```

#####From `_ElemY`

>```cpp
int nResult = 0;
basic_string< wchar_t > strUNICODE;
strUNICODE.format("Result is %d", nResult);
>```

#####Warning

You should not use `_ElemX` string and `_ElemY` string at the same time as arguments of `format` function. Like this:

>```cpp
basic_string< wchar_t > strUNICODE;
strUNICODE.format("This example is %s.\n", L"incorrect");
>```

####Convert from/to UTF-8

#####Explicit converting

>```cpp
basic_string< ... > strFirst;
std::string strUtf8 = strFirst.toutf8();
basic_string< ... > strSecond;
strSecond.fromutf8(strUtf8);
>```

#####Limitation

`basic_string` template class can't determine whether string is ASCII or UTF-8.
