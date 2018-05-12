
## Streams

---
<https://github.com/mlach9u/col/tree/master/src/col_stream>

### 목적

STL을 확장하였으며 아래와 같은 내용이 포함됩니다.

1. 새로운 stream 정의
2. 새로운 manipulator 정의

### 새로운 stream 정의

*수(Arithmetic)의 입출력 시퀀스 재정의*

`std::num_put` 및 `std::num_get`을 확장하여 `num_put_interface`, `num_put`과 `num_get_interface`, `num_get`을 정의하였으며 이는 숫자의 입출력 시퀀스를 재정의할 수 있도록 구조를 만들기 위함입니다.

각 클래스는 아래와 같이 선언됩니다.

```cpp
template< typename _Elem, typename _OutIt >
class num_put_interface : public std::num_put< _Elem, _OutIt >;
```

```cpp
template< typename _Elem, typename _OutIt,
	template< typename _Elem, typename _OutIt > class _NputOper
>
class num_put : public num_put_interface< _Elem, _OutIt >;
```

```cpp
template< typename _Elem, typename _InIt >
class num_get_interface : public std::num_get< _Elem, _InIt >;
```

```cpp
template< typename _Elem, typename _InIt,
	template< typename _Elem, typename _InIt > class _NgetOper
>
class num_get : public num_get_interface< _Elem, _InIt >;
```

앞에 새로 정의한 클래스와 함께 사용할 수 있도록 `std::basic_ostream`과 `std::basic_istream`을 확장하여 `basic_otream`, `basic_istream`을 정의하여 아래와 같이 연산자를 오버로딩하였습니다.

```cpp
template< typename _Elem, typename _Traits = std::char_traits< _Elem > >
class basic_ostream : public std::basic_ostream< _Elem, _Traits >
{
	_Myt& operator<<(bool _Val) { return _Put_arithmetic(_Val); }
	_Myt& operator<<(char _Val) { return _Put_arithmetic(_Val); }
	_Myt& operator<<(unsigned char _Val) { return _Put_arithmetic(_Val); }
	_Myt& operator<<(wchar_t _Val) { return _Put_arithmetic((short)_Val); }
	_Myt& operator<<(short _Val) { return _Put_arithmetic(_Val); }
	_Myt& operator<<(unsigned short _Val) { return _Put_arithmetic(_Val); }
	_Myt& operator<<(int _Val) { return _Put_arithmetic(_Val); }
	_Myt& operator<<(unsigned int _Val) { return _Put_arithmetic(_Val); }
	_Myt& operator<<(long _Val) { return _Put_arithmetic(_Val); }
	_Myt& operator<<(unsigned long _Val) { return _Put_arithmetic(_Val); }
	_Myt& operator<<(long long _Val) { return _Put_arithmetic(_Val); }
	_Myt& operator<<(unsigned long long _Val) { return _Put_arithmetic(_Val); }
	_Myt& operator<<(float _Val) { return _Put_arithmetic(_Val); }
	_Myt& operator<<(double _Val) { return _Put_arithmetic(_Val); }
	_Myt& operator<<(long double _Val) { return _Put_arithmetic(_Val); }
	_Myt& operator<<(_Myt& (__cdecl *_Pfn)(_Myt&)) { return ((*_Pfn)(*this)); }
	_Myt& operator<<(_Base& (__cdecl *_Pfn)(_Base&)) { _Base::operator<<(_Pfn); return *this; }
	_Myt& operator<<(_Myios& (__cdecl *_Pfn)(_Myios&)) { _Base::operator<<(_Pfn); return *this; }
	_Myt& operator<<(std::ios_base& (__cdecl *_Pfn)(std::ios_base&)) { _Base::operator<<(_Pfn); return *this; }
	_Myt& operator<<(const _Elem* p) { *(_Base*)this << p; return *this; }
};
```

```cpp
template< typename _Elem, typename _Traits = std::char_traits< _Elem > >
class basic_istream : public std::basic_istream< _Elem, _Traits >
{
	_Myt& operator>>(bool& _Val) { return _Get_arithmetic(_Val); }
	_Myt& operator>>(char& _Val) { return _Get_arithmetic(_Val); }
	_Myt& operator>>(unsigned char& _Val) { return _Get_arithmetic(_Val); }
	_Myt& operator>>(wchar_t& _Val) { return _Get_arithmetic((short&)_Val); }
	_Myt& operator>>(short& _Val) { return _Get_arithmetic(_Val); }
	_Myt& operator>>(unsigned short& _Val) { return _Get_arithmetic(_Val); }
	_Myt& operator>>(int& _Val) { return _Get_arithmetic(_Val); }
	_Myt& operator>>(unsigned int& _Val) { return _Get_arithmetic(_Val); }
	_Myt& operator>>(long& _Val) { return _Get_arithmetic(_Val); }
	_Myt& operator>>(unsigned long& _Val) { return _Get_arithmetic(_Val); }
	_Myt& operator>>(long long& _Val) { return _Get_arithmetic(_Val); }
	_Myt& operator>>(unsigned long long& _Val) { return _Get_arithmetic(_Val); }
	_Myt& operator>>(float& _Val) { return _Get_arithmetic(_Val); }
	_Myt& operator>>(double& _Val) { return _Get_arithmetic(_Val); }
	_Myt& operator>>(long double& _Val) { return _Get_arithmetic(_Val); }
	_Myt& operator>>(_Myt& (__cdecl *_Pfn)(_Myt&)) { return ((*_Pfn)(*this)); }
	_Myt& operator>>(_Base& (__cdecl *_Pfn)(_Base&)) { _Base::operator>>(_Pfn); return *this; }
	_Myt& operator>>(_Myios& (__cdecl *_Pfn)(_Myios&)) { _Base::operator>>(_Pfn); return *this; }
	_Myt& operator>>(std::ios_base& (__cdecl *_Pfn)(std::ios_base&)) { _Base::operator>>(_Pfn); return *this; }
}
```

*binary Stream 정의*

이 클래스는 binary를 사용한 stream 입출력이 구현되어 있습니다. 이는 STL의 stream은 사람이 읽을 수 있는 코드의 입출력이 구현되어 있기 때문입니다.

위에서 새로 정의한 클래스를 확장하여 `basic_bostream`, `basic_bistream`을 정의하였으며, `std::basic_stringbuf`를 확장하여 `basic_binarybuf`를 정의하였습니다. 이는 binary stream을 메모리에서 사용하기 위함입니다.

이 클래스들은 아래처럼 사용할 수 있습니다.

```cpp
int i = 10;
long l = 20;
float f = 30.0;
basic_binarybuf<char> buf;
basic_bostream<char> bos(&buf);
basic_bistream<char> bis(&buf);
bos << i << l << f;
bis >> i >> l >> f;
```

또한 아래처럼 다른 표준 stream 버퍼를 사용할 수 있습니다.

```cpp
std::basic_ofstrea<char> of(filename);
basic_bostream<char> bos(of.rdbuf());
```

### 새로운 manipulator 정의

*`bins` 및 `nobins` 정의*

이 manipulator는 아래와 같은 작업을 진행합니다.

1. binary 입출력을 활성화합니다.
2. binary 입출력을 비활성화합니다.

이 manipulator는 아래처럼 표준 stream에 사용할 수 있습니다.

```cpp
std::cout << bins << (int)0x30313233 << nobins << std::endl;
// result : 3210
```
