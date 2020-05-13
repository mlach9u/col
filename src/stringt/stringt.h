#ifndef __STRINGT_H__
#define __STRINGT_H__

#include "xstringt.h"

template< typename _Elem,
    typename _Traits = std::char_traits< _Elem >,
    typename _Ax = std::allocator< _Elem >
>
class basic_string : public std::basic_string< _Elem, _Traits, _Ax >
{
public:
    static_assert(is_char< _Elem >::value, "_Elem must be char type.");

    typedef std::basic_string< _Elem > _Base;

    typedef typename _Base::value_type value_type;
    typedef typename _Base::size_type size_type;
    typedef typename _Base::difference_type difference_type;
    typedef typename _Base::pointer pointer;
    typedef typename _Base::const_pointer const_pointer;
    typedef typename _Base::reference reference;
    typedef typename _Base::const_reference const_reference;
    typedef typename _Base::iterator iterator;
    typedef typename _Base::const_iterator const_iterator;
    typedef typename _Base::reverse_iterator reverse_iterator;
    typedef typename _Base::const_reverse_iterator const_reverse_iterator;

    typedef CharType_Implement< _Elem > _Implement;
    typedef typename _Implement::_ElemX _ElemX;
    typedef typename _Implement::_ElemY _ElemY;
    typedef typename _Implement::_StrX _StrX;
    typedef typename _Implement::_StrY _StrY;

    typedef basic_string< _ElemX > _ThisX;
    typedef basic_string< _ElemY > _ThisY;

    basic_string() {}
    basic_string(const _ElemX* lpsz) : _Base(lpsz) {}
    basic_string(const _StrX& str) : _Base(str) {}
    basic_string(const _ThisX& str) : _Base(str.c_str()) {}
    basic_string(const _ElemY* lpsz) { fromY(lpsz); }
    basic_string(const _StrY& str) { fromY(str); }
    basic_string(const _ThisY& str) { fromY(str); }

private:
    void _formatV(const _ElemX* lpszFormat, va_list v)
    {
        _Implement::_formatV(*this, lpszFormat, v);
    }

    void _formatV(const _ElemY* lpszFormat, va_list v)
    {
        _ThisY strY;
        strY.formatV(lpszFormat, v);
        fromY(strY);
    }

public:
    template< typename TYPE >
    void formatV(const TYPE* lpszFormat, va_list v)
    {
        _formatV(lpszFormat, v);
    }

    template< typename TYPE >
    void format(const TYPE* lpszFormat, ...)
    {
        va_list v;
        va_start(v, lpszFormat);
        _formatV(lpszFormat, v);
        va_end(v);
    }

public:
    _StrY toY(unsigned int nCodePage = cpnDefault) const
    {
        _StrY strRet;
        _Implement::xtoy(strRet, *this, nCodePage);
        return strRet;
    }

    const _StrX& fromY(const _ElemY* lpszSrc, unsigned int nCodePage = cpnDefault)
    {
        _Implement::ytox(*this, lpszSrc, nCodePage);
        return *this;
    }

    const _StrX& fromY(const _StrY& strSrc, unsigned int nCodePage = cpnDefault)
    {
        return fromY(strSrc.c_str(), nCodePage);
    }

public:
    std::string toutf8() const
    {
        std::string strRet;
        _Implement::xtoutf8(strRet, *this);
        return strRet;
    }

    const _StrX& fromutf8(const char* lpszSrc)
    {
        _Implement::utf8tox(*this, lpszSrc);
        return *this;
    }

    const _StrX& fromutf8(const std::string& strSrc)
    {
        return fromutf8(strSrc.c_str());
    }

public:
    const _StrX& normalize(UnicodeNormalizationForm unf)
    {
        _StrX str;
        _Implement::normalize(str, this->c_str(), unf);
        return *this;
    }

public:
    const _ThisX& replace(const _ElemX* lpszFrom, const _ElemX* lpszTo)
    {
        size_type _Off;
        while ((_Off = _Base::find(lpszFrom)) != _Base::npos)
            _Base::replace(_Off, _Traits::length(lpszFrom), lpszTo);
        return *this;
    }

    const _ThisX & replace(const _ElemX * lpszFrom, const _ElemY * lpszTo)
    {
        return replace(lpszFrom, _ThisX(lpszTo).c_str());
    }

    const _ThisX& replace(const _ElemY * lpszFrom, const _ElemX * lpszTo)
    {
        return replace(_ThisX(lpszFrom).c_str(), lpszTo);
    }

    const _ThisX& replace(const _ElemY * lpszFrom, const _ElemY * lpszTo)
    {
        return replace(_ThisX(lpszFrom).c_str(), _ThisX(lpszTo).c_str());
    }

public:
    const _ThisX& tolower()
    {
        std::transform(_Base::begin(), _Base::end(), _Base::begin(), _Implement::tolower);
        return *this;
    }

    const _ThisX& toupper()
    {
        std::transform(_Base::begin(), _Base::end(), _Base::begin(), _Implement::toupper);
        return *this;
    }

public:
    operator const _ElemX* () const { return _Base::c_str(); }

public:
    const _Base& operator = (const _ElemX* lpsz) { _Base::assign(lpsz); return *this; }
    const _Base& operator = (const _StrX& str) { _Base::assign(str); return *this; }
    const _Base& operator = (const _ThisX& str) { _Base::assign(str); return *this; }
    const _Base& operator = (const _ElemY* lpsz) { return fromY(lpsz); }
    const _Base& operator = (const _StrY& str) { return fromY(str); }
    const _Base& operator = (const _ThisY& str) { return fromY(str); }

public:
    const _Base& operator += (const _ElemX* lpsz) { _Base::append(lpsz); return *this; }
    const _Base& operator += (const _StrX& str) { _Base::append(str); return *this; }
    const _Base& operator += (const _ThisX& str) { _Base::append(str); return *this; }
    const _Base& operator += (const _ElemY* lpsz) { _Base::append(_ThisX(lpsz)); return *this; }
    const _Base& operator += (const _StrY& str) { _Base::append(_ThisX(str)); return *this; }
    const _Base& operator += (const _ThisY& str) { _Base::append(_ThisX(str)); return *this; }
};

typedef basic_string< char > string;
typedef basic_string< wchar_t > wstring;

#endif
