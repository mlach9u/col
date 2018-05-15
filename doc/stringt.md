
## String
---
<https://github.com/mlach9u/col/tree/master/src/stringt>

### 목적

이 클래스는 STL의 `std::basic_string`을 확장하였으며, ASCII와 UNICODE, UTF-8 사이의 변환을 손쉽게 하기 위하여 설계되었습니다.

### 개념

이 클래스는 두 개의 Element 형식을 가지고 있습니다. `_ElemX`와 `_ElemY`가 그것입니다. 이 개념은 MFC의 `CString` 클래스를 벤치마킹 하였습니다. 템플릿 인수에 따른 각 Element 형식은 아래와 같습니다.

```cpp
basic_string< char >::_ElemX // is char
basic_string< char >::_ElemY // is wchar_t
basic_string< wchar_t >::_ElemX // is wchar_t
basic_string< wchar_t >::_ElemY // is char
```

위와 유사하게 아래와 같은 형식도 존재합니다.

```cpp
basic_string< ... >::_StrX // is std::basic_string< _ElemX >
basic_string< ... >::_StrY // is std::basic_string< _ElemY >
basic_string< ... >::_ThisX // is basic_string< _ElemX >
basic_string< ... >::_ThisY // is basic_string< _ElemY >
```

### 사용법

*ASCII 와 UNICODE 사이의 변환*

#### 생성자 사용

```cpp
std::cout << basic_string<char>(L"Hello, World!") << std::endl;
std::wcout << basic_string<wchar_t>("Hello, World!") << std::endl;
```

#### 대입 연산자 사용

```cpp
basic_string< wchar_t > strUNICODE;
strUNICODE = "Hello World!";
std::wcout << strUNICODE << std::endl;
```

#### 명시적 변환

```cpp
basic_string<char> strANSI;
strANSI.fromY(L"Hello, World!");
std::cout << strANSI << std::endl;
std::wcout << strANSI.toY() << std::endl;
```

#### 서식문자열 사용

```cpp
int nResult = 0;
basic_string< char > strANSI;
strANSI.format("Result is %d", nResult);
std::cout << strANSI << std::endl;
```

```cpp
int nResult = 0;
basic_string< wchar_t > strUNICODE;
strUNICODE.format("Result is %d", nResult);
std::wcout << strUNICODE << std::endl;
```

*UTF-8 과의 변환*

#### 명시적 변환

```cpp
basic_string< ... > strFirst;
std::string strUtf8 = strFirst.toutf8();
basic_string< ... > strSecond;
strSecond.fromutf8(strUtf8);
```

### 주의사항

1. 이 클래스의 함수들은 locale 정보의 영향을 받습니다. 자세한 정보는 [setlocale](http://www.cplusplus.com/reference/clocale/setlocale/)을 참고하세요.
2. 서식문자열 사용시, `format`함수의 인수로 `_ElemX`형식과 `_ElemY`형식을 혼용해서는 안됩니다.
3. 이 클래스는 인수로 전달된 문자열이 ASCII인지 UTF-8인지 구분할 수 없습니다.
