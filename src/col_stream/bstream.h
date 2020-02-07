#ifndef __BSTREAM_H__
#define __BSTREAM_H__

#include "col_stream.h"

template< typename _Elem, typename _OutIt >
struct bin_num_put_operator
{
    template< typename _Vty >
    _OutIt operator()(_OutIt _Dest, std::ios_base& _Iosbase, _Elem _Fill, _Vty _Val) const
    {
        COL_UNREFERENCE_PARAMETER(_Iosbase);
        COL_UNREFERENCE_PARAMETER(_Fill);
        const int _Cch = (sizeof(_Vty) / sizeof(_Elem)) + (sizeof(_Vty) % sizeof(_Elem));
        _Elem _Buff[_Cch];
        memset(_Buff, 0, _Cch * sizeof(_Elem));
        memcpy(_Buff, &_Val, sizeof(_Vty));
        for (int i = 0; i < _Cch; i++, _Dest++)
            *_Dest = _Buff[i];
        return _Dest;
    }
};

template< typename _Elem, typename _InIt >
struct bin_num_get_operator
{
    template< typename _Vty >
    _InIt operator()(_InIt _First, _InIt _Last, std::ios_base& _Iosbase, std::ios_base::iostate& _State, _Vty& _Val) const
    {
        COL_UNREFERENCE_PARAMETER(_Iosbase);
        const int _Cch = (sizeof(_Vty) / sizeof(_Elem)) + (sizeof(_Vty) % sizeof(_Elem));
        _Elem _Buff[_Cch] = { 0, };

        int i;
        for (i = 0; (i < _Cch) && (_First != _Last); i++, _First++)
            _Buff[i] = *_First;
        if (_First == _Last)
        {
            _State |= std::ios_base::eofbit;
            memset(&_Buff[i], _Elem(), (((size_t)_Cch - i) * sizeof(_Elem)));
        }
        memcpy(&_Val, _Buff, sizeof(_Vty));
        return _First;
    }
};

template< typename _Elem, typename _Traits >
std::basic_ostream< _Elem, _Traits >& __cdecl bins(std::basic_ostream< _Elem, _Traits >& _Ostr)
{
    typedef typename basic_ostream< _Elem, _Traits >::_Iter _Iter;
    typedef typename basic_ostream< _Elem, _Traits >::_Nput _Nput;
    typedef typename basic_ostream< _Elem, _Traits >::_col_Nput _col_Nput;

    typedef num_put< _Elem, _Iter, bin_num_put_operator > _bin_Nput;

    if (dynamic_cast<const _col_Nput*>(&(std::use_facet< _Nput >(_Ostr.getloc()))) == 0)
        _Ostr.imbue(std::locale(_Ostr.getloc(), new _bin_Nput()));
    _Ostr.iword(__col_stream_index__) |= __col_sfNput;
    return _Ostr;
}

template< typename _Elem, typename _Traits >
std::basic_ostream< _Elem, _Traits >& __cdecl nobins(std::basic_ostream< _Elem, _Traits > & _Ostr)
{
    typedef typename basic_ostream< _Elem, _Traits >::_Nput _Nput;
    typedef typename basic_ostream< _Elem, _Traits >::_col_Nput _col_Nput;

    _Ostr.iword(__col_stream_index__) &= ~__col_sfNput;
    if (dynamic_cast<const _col_Nput*>(&(std::use_facet< _Nput >(_Ostr.getloc()))) != 0)
        _Ostr.imbue(std::locale(_Ostr.getloc(), new _Nput));
    return _Ostr;
}

template< typename _Elem, typename _Traits >
std::basic_istream< _Elem, _Traits >& __cdecl bins(std::basic_istream< _Elem, _Traits > & _Istr)
{
    typedef typename basic_istream< _Elem, _Traits >::_Iter _Iter;
    typedef typename basic_istream< _Elem, _Traits >::_Nget _Nget;
    typedef typename basic_istream< _Elem, _Traits >::_col_Nget _col_Nget;

    typedef num_get< _Elem, _Iter, bin_num_get_operator > _bin_Nget;

    std::noskipws(_Istr);
    if (dynamic_cast<const _col_Nget*>(&(std::use_facet< _Nget >(_Istr.getloc()))) == 0)
        _Istr.imbue(std::locale(_Istr.getloc(), new _bin_Nget));
    _Istr.iword(__col_stream_index__) |= __col_sfNget;
    return _Istr;
}

template< typename _Elem, typename _Traits >
std::basic_istream< _Elem, _Traits >& __cdecl nobins(std::basic_istream< _Elem, _Traits > & _Istr)
{
    typedef typename basic_istream< _Elem, _Traits >::_Nget _Nget;
    typedef typename basic_istream< _Elem, _Traits >::_col_Nget _col_Nget;

    _Istr.iword(__col_stream_index__) &= ~__col_sfNget;
    if (dynamic_cast<const _col_Nget*>(&(std::use_facet< _Nget >(_Istr.getloc()))) != 0)
        _Istr.imbue(std::locale(_Istr.getloc(), new _Nget));
    std::skipws(_Istr);
    return _Istr;
}

template< typename _Elem, typename _Traits = std::char_traits< _Elem >, typename _Alloc = std::allocator< _Elem > >
class basic_binarybuf : public std::basic_stringbuf< _Elem, _Traits, _Alloc >
{
public:
    typedef std::basic_stringbuf< _Elem, _Traits, _Alloc > _Base;
    typedef typename _Base::_Mystr _Mystr;

    basic_binarybuf() {}

    explicit basic_binarybuf(const _Mystr& _Str)
        : _Base(_Str) {}

    basic_binarybuf(const _Elem* _Ptr, size_t _Count)
    {
        _Init(_Ptr, _Count, 0);
        _Base::setp(_Base::pbase(), _Base::epptr(), _Base::epptr());
    }

    const _Elem* ptr() const
    {
        return _Base::eback();
    }

    size_t size() const
    {
        return ((_Base::pptr() == 0) ? 0 : (_Base::pptr() - _Base::eback()));
    }
};

template< typename _Elem, typename _Traits = std::char_traits< _Elem > >
class basic_bostream : public basic_ostream< _Elem, _Traits >
{
public:
    typedef basic_bostream< _Elem, _Traits > _Myt;
    typedef basic_ostream< _Elem, _Traits > _Base;
    typedef typename _Base::_Myios _Myios;
    typedef typename _Base::_Mysb _Mysb;

    explicit basic_bostream(_Mysb* _Strbuf)
        : _Base(_Strbuf)
    {
        bins(*this);
    }

    template< typename _Vty >
    _Myt& _Put_arithmetic(_Vty _Val)
    {
        _Base::_Put_arithmetic(_Val);
        return *this;
    }

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

    _Myt& operator<<(_Myt& (__cdecl* _Pfn)(_Myt&))
    {
        return ((*_Pfn)(*this));
    }

    _Myt& operator<<(_Base& (__cdecl* _Pfn)(_Base&))
    {
        _Base::operator<<(_Pfn); return *this;
    }

    _Myt& operator<<(_Myios& (__cdecl* _Pfn)(_Myios&))
    {
        _Base::operator<<(_Pfn); return *this;
    }

    _Myt& operator<<(std::ios_base& (__cdecl* _Pfn)(std::ios_base&))
    {
        _Base::operator<<(_Pfn); return *this;
    }

    _Myt& operator<<(const _Elem* p)
    {
        *(_Base*)this << p; return *this;
    }
};

template< typename _Elem, typename _Traits = std::char_traits< _Elem > >
class basic_bistream : public basic_istream< _Elem, _Traits >
{
public:
    typedef basic_bistream< _Elem, _Traits > _Myt;
    typedef basic_istream< _Elem, _Traits > _Base;
    typedef typename _Base::_Myios _Myios;
    typedef typename _Base::_Mysb _Mysb;

    explicit basic_bistream(_Mysb* _Strbuf)
        : _Base(_Strbuf)
    {
        bins(*this);
    }

    template< typename _Vty >
    _Myt& _Get_arithmetic(_Vty& _Val)
    {
        _Base::_Get_arithmetic(_Val);
        return *this;
    }

    _Myt& operator >> (bool& _Val) { return _Get_arithmetic(_Val); }
    _Myt& operator >> (char& _Val) { return _Get_arithmetic(_Val); }
    _Myt& operator >> (unsigned char& _Val) { return _Get_arithmetic(_Val); }
    _Myt& operator >> (wchar_t& _Val) { return _Get_arithmetic((short&)_Val); }
    _Myt& operator >> (short& _Val) { return _Get_arithmetic(_Val); }
    _Myt& operator >> (unsigned short& _Val) { return _Get_arithmetic(_Val); }
    _Myt& operator >> (int& _Val) { return _Get_arithmetic(_Val); }
    _Myt& operator >> (unsigned int& _Val) { return _Get_arithmetic(_Val); }
    _Myt& operator >> (long& _Val) { return _Get_arithmetic(_Val); }
    _Myt& operator >> (unsigned long& _Val) { return _Get_arithmetic(_Val); }
    _Myt& operator >> (long long& _Val) { return _Get_arithmetic(_Val); }
    _Myt& operator >> (unsigned long long& _Val) { return _Get_arithmetic(_Val); }
    _Myt& operator >> (float& _Val) { return _Get_arithmetic(_Val); }
    _Myt& operator >> (double& _Val) { return _Get_arithmetic(_Val); }
    _Myt& operator >> (long double& _Val) { return _Get_arithmetic(_Val); }

    _Myt& operator >> (_Myt& (__cdecl* _Pfn)(_Myt&))
    {
        return ((*_Pfn)(*this));
    }

    _Myt& operator >> (_Base& (__cdecl* _Pfn)(_Base&))
    {
        _Base::operator >> (_Pfn); return *this;
    }

    _Myt& operator >> (_Myios& (__cdecl* _Pfn)(_Myios&))
    {
        _Base::operator >> (_Pfn); return *this;
    }

    _Myt& operator >> (std::ios_base& (__cdecl* _Pfn)(std::ios_base&))
    {
        _Base::operator >> (_Pfn); return *this;
    }
};

typedef basic_binarybuf< char > binarybuf;
typedef basic_bostream< char > bostream;
typedef basic_bistream< char > bistream;

#endif
