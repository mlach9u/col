#ifndef __COL_STREAM_H__
#define __COL_STREAM_H__

#include "col_xstream.h"

extern int __col_stream_index__;
//int __col_stream_index__ = std::ios_base::xalloc();

enum __col_Stream_Flag
{
    __col_sfNput = 0x00000001,
    __col_sfNget = 0x00000002,

    __col_sfLast = 0x00000000
};

template< typename _Elem, typename _Traits = std::char_traits< _Elem > >
class basic_ostream : public std::basic_ostream< _Elem, _Traits >
{
public:
    typedef basic_ostream< _Elem, _Traits > _Myt;
    typedef std::basic_ostream< _Elem, _Traits > _Base;
    typedef typename _Base::_Myios _Myios;
    typedef typename _Base::_Mysb _Mysb;
    typedef typename _Base::_Iter _Iter;
    typedef typename _Base::_Nput _Nput;

    typedef num_put_interface< _Elem, _Iter > _col_Nput;

    explicit basic_ostream(_Mysb* _Strbuf)
        : _Base(_Strbuf)
    {
    }

    typedef typename _Base::sentry sentry;

    template< typename _Vty >
    _Myt& _Put_arithmetic(_Vty _Val)
    {
        static_assert(is_arithmetic< _Vty >::value, "Integer or floating point required");
        if ((_Base::iword(__col_stream_index__) & __col_sfNput) == 0)
        {
            *(_Base*)this << _Val;
            return *this;
        }

        std::ios_base::iostate _State = std::ios_base::goodbit;
        const sentry _Ok(*this);

        if (_Ok)
        {
            try
            {
                const _col_Nput* p = dynamic_cast<const _col_Nput*>(&(std::use_facet< _Nput >(_Base::getloc())));
                if ((p == 0) || (p->put(_Iter(_Myios::rdbuf()), *this, _Myios::fill(), _Val).failed()))
                    _State |= std::ios_base::badbit;
            }
            catch (...)
            {
                _Myios::setstate(std::ios_base::badbit, true);
            }
        }

        _Myios::setstate(_State);
        return (*this);
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

    _Myt& operator<<(_Myt & (__cdecl * _Pfn)(_Myt&))
    {
        return ((*_Pfn)(*this));
    }

    _Myt& operator<<(_Base & (__cdecl * _Pfn)(_Base&))
    {
        _Base::operator<<(_Pfn); return *this;
    }

    _Myt& operator<<(_Myios & (__cdecl * _Pfn)(_Myios&))
    {
        _Base::operator<<(_Pfn); return *this;
    }

    _Myt& operator<<(std::ios_base & (__cdecl * _Pfn)(std::ios_base&))
    {
        _Base::operator<<(_Pfn); return *this;
    }

    _Myt& operator<<(const _Elem * p)
    {
        *(_Base*)this << p; return *this;
    }
};

template< typename _Elem, typename _Traits = std::char_traits< _Elem > >
class basic_istream : public std::basic_istream< _Elem, _Traits >
{
public:
    typedef basic_istream< _Elem, _Traits > _Myt;
    typedef std::basic_istream< _Elem, _Traits > _Base;
    typedef typename _Base::_Myios _Myios;
    typedef typename _Base::_Mysb _Mysb;
    typedef typename _Base::_Iter _Iter;
    typedef typename _Base::_Nget _Nget;

    typedef num_get_interface< _Elem, _Iter > _col_Nget;

    explicit basic_istream(_Mysb* _Strbuf)
        : _Base(_Strbuf)
    {
    }

    typedef typename _Base::sentry sentry;

    template< typename _Vty >
    _Myt& _Get_arithmetic(_Vty& _Val)
    {
        static_assert(is_arithmetic< _Vty >::value, "Integer or floating point required");
        if ((_Base::iword(__col_stream_index__) & __col_sfNget) == 0)
        {
            *(_Base*)this >> _Val;
            return *this;
        }

        std::ios_base::iostate _State = std::ios_base::goodbit;
        const sentry _Ok(*this);

        if (_Ok)
        {
            try
            {
                const _col_Nget* p = dynamic_cast<const _col_Nget*>(&(std::use_facet< _Nget >(_Base::getloc())));
                if (p == 0)
                    _State |= std::ios_base::badbit;
                else
                    p->get(_Iter(_Myios::rdbuf()), _Iter(0), *this, _State, _Val);
            }
            catch (...)
            {
                _Myios::setstate(std::ios_base::badbit, true);
            }
        }

        _Myios::setstate(_State);
        return (*this);
    }

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

    _Myt& operator>>(_Myt & (__cdecl * _Pfn)(_Myt&))
    {
        return ((*_Pfn)(*this));
    }

    _Myt& operator>>(_Base & (__cdecl * _Pfn)(_Base&))
    {
        _Base::operator>>(_Pfn); return *this;
    }

    _Myt& operator>>(_Myios & (__cdecl * _Pfn)(_Myios&))
    {
        _Base::operator>>(_Pfn); return *this;
    }

    _Myt& operator>>(std::ios_base & (__cdecl * _Pfn)(std::ios_base&))
    {
        _Base::operator>>(_Pfn); return *this;
    }
};

typedef basic_ostream< char > ostream;
typedef basic_istream< char > istream;
typedef basic_ostream< wchar_t > wostream;
typedef basic_istream< wchar_t > wistream;

#endif
