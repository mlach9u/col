
## Collection of Libraries base

---
<https://github.com/mlach9u/col/tree/master/src/col_base>

### 목적

모든 COL 프로젝트의 기반이 되는 프로젝트이며, 아래와 같은 내용이 포함됩니다.

1. 여러 C++ Feature를 현재 컴파일 중인 Visual Studio 버전에서 사용 가능한지 판단할 수 있는 정의문
2. 자주 사용되는 매크로
3. 사용할 수 없는 일부 C++ Feature를 사용가능하도록 하는 정의문

### C++ Features

Visual Studio 버전이 5개로 구분되어 있으며, 현재 COL 프로젝트에서 사용되는 문법의 사용 가능 여부가 정의되어 있습니다. 각 문법의 사용 가능 여부는 <https://msdn.microsoft.com/en-us/library/hh567368.aspx>을 참고하여 구성하였습니다.

Visual Studio 2010 이전 버전에서는 `static_assert`문법을 사용할 수 없지만 이 프로젝트를 포함하면 그와 유사하게 동작하는 코드를 작성할 수 있습니다. 이 코드는 아래와 같이 구현됩니다.

```cpp
#if !__COL_STATIC_ASSERT__
template< bool b > struct __col_static_assert_test {};
template<> struct __col_static_assert_test< false >;
template< int n > struct __col_static_assert_base {};
#define __col_static_assert(exp, msg, count)\
	typedef __col_static_assert_base<\
		sizeof(__col_static_assert_test< exp >)\
	> COL_GLUE(__col_static_assert_type, count)
#define static_assert(exp, msg) __col_static_assert(exp, msg, __COUNTER__)
#endif
```

`static_assert`와 동일하게 컴파일 시 오류를 검사할 수 있지만 지정한 문자열이 출력창에 표시되지 않으며 오류 문구도 정확하지 않습니다.

### 자주 사용되는 매크로 정의

아래와 같은 자주 사용되는 매크로를 미리 정의하였습니다.

*COL_GLUE*

두 글자를 연결시키는 매크로입니다.

```cpp
#define COL_GLUE2(a, b) a##b
#define COL_GLUE1(a, b) COL_GLUE2(a, b)
#define COL_GLUE(a, b) COL_GLUE1(a, b)
```

*COL_STRING*

지정된 글자를 문자열 리터럴로 변환하는 매크로입니다.

```cpp
#define COL_STRING2(a) #a
#define COL_STRING1(a) COL_STRING2(a)
#define COL_STRING(a) COL_STRING1(a)
```
