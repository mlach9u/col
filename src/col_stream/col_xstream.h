#ifndef __COL_XSTREAM_H__
#define __COL_XSTREAM_H__

#include "inclusion_col_stream.h"
#include "..\\col_type_traits\\col_type_traits.h"

template< typename _Elem, typename _OutIt >
class num_put_interface : public std::num_put< _Elem, _OutIt >
{
protected:
    virtual _OutIt do_put(_OutIt _Dest, std::ios_base& _Iosbase, _Elem _Fill, bool _Val) const = 0;
    virtual _OutIt do_put(_OutIt _Dest, std::ios_base& _Iosbase, _Elem _Fill, char _Val) const = 0;
    virtual _OutIt do_put(_OutIt _Dest, std::ios_base& _Iosbase, _Elem _Fill, unsigned char _Val) const = 0;
    virtual _OutIt do_put(_OutIt _Dest, std::ios_base& _Iosbase, _Elem _Fill, short _Val) const = 0;
    virtual _OutIt do_put(_OutIt _Dest, std::ios_base& _Iosbase, _Elem _Fill, unsigned short _Val) const = 0;
    virtual _OutIt do_put(_OutIt _Dest, std::ios_base& _Iosbase, _Elem _Fill, int _Val) const = 0;
    virtual _OutIt do_put(_OutIt _Dest, std::ios_base& _Iosbase, _Elem _Fill, unsigned int _Val) const = 0;
    virtual _OutIt do_put(_OutIt _Dest, std::ios_base& _Iosbase, _Elem _Fill, long _Val) const = 0;
    virtual _OutIt do_put(_OutIt _Dest, std::ios_base& _Iosbase, _Elem _Fill, unsigned long _Val) const = 0;
    virtual _OutIt do_put(_OutIt _Dest, std::ios_base& _Iosbase, _Elem _Fill, long long _Val) const = 0;
    virtual _OutIt do_put(_OutIt _Dest, std::ios_base& _Iosbase, _Elem _Fill, unsigned long long _Val) const = 0;
    virtual _OutIt do_put(_OutIt _Dest, std::ios_base& _Iosbase, _Elem _Fill, float _Val) const = 0;
    virtual _OutIt do_put(_OutIt _Dest, std::ios_base& _Iosbase, _Elem _Fill, double _Val) const = 0;
    virtual _OutIt do_put(_OutIt _Dest, std::ios_base& _Iosbase, _Elem _Fill, long double _Val) const = 0;
public:
    template< typename _Vty >
    _OutIt put(_OutIt _Dest, std::ios_base& _Iosbase, _Elem _Fill, _Vty _Val) const
    {
        return do_put(_Dest, _Iosbase, _Fill, _Val);
    }
};

template< typename _Elem, typename _OutIt,
    template< typename _Elem, typename _OutIt > class _NputOper
>
class num_put : public num_put_interface< _Elem, _OutIt >
{
private:
    _NputOper< _Elem, _OutIt > op;

    template< typename _Vty >
    _OutIt col_put(_OutIt _Dest, std::ios_base& _Iosbase, _Elem _Fill, _Vty _Val) const
    {
        return op(_Dest, _Iosbase, _Fill, _Val);
    }
protected:
    virtual _OutIt do_put(_OutIt _Dest, std::ios_base& _Iosbase, _Elem _Fill, bool _Val) const
    {
        return col_put(_Dest, _Iosbase, _Fill, _Val);
    }
    virtual _OutIt do_put(_OutIt _Dest, std::ios_base& _Iosbase, _Elem _Fill, char _Val) const
    {
        return col_put(_Dest, _Iosbase, _Fill, _Val);
    }
    virtual _OutIt do_put(_OutIt _Dest, std::ios_base& _Iosbase, _Elem _Fill, unsigned char _Val) const
    {
        return col_put(_Dest, _Iosbase, _Fill, _Val);
    }
    virtual _OutIt do_put(_OutIt _Dest, std::ios_base& _Iosbase, _Elem _Fill, short _Val) const
    {
        return col_put(_Dest, _Iosbase, _Fill, _Val);
    }
    virtual _OutIt do_put(_OutIt _Dest, std::ios_base& _Iosbase, _Elem _Fill, unsigned short _Val) const
    {
        return col_put(_Dest, _Iosbase, _Fill, _Val);
    }
    virtual _OutIt do_put(_OutIt _Dest, std::ios_base& _Iosbase, _Elem _Fill, int _Val) const
    {
        return col_put(_Dest, _Iosbase, _Fill, _Val);
    }
    virtual _OutIt do_put(_OutIt _Dest, std::ios_base& _Iosbase, _Elem _Fill, unsigned int _Val) const
    {
        return col_put(_Dest, _Iosbase, _Fill, _Val);
    }
    virtual _OutIt do_put(_OutIt _Dest, std::ios_base& _Iosbase, _Elem _Fill, long _Val) const
    {
        return col_put(_Dest, _Iosbase, _Fill, _Val);
    }
    virtual _OutIt do_put(_OutIt _Dest, std::ios_base& _Iosbase, _Elem _Fill, unsigned long _Val) const
    {
        return col_put(_Dest, _Iosbase, _Fill, _Val);
    }
    virtual _OutIt do_put(_OutIt _Dest, std::ios_base& _Iosbase, _Elem _Fill, long long _Val) const
    {
        return col_put(_Dest, _Iosbase, _Fill, _Val);
    }
    virtual _OutIt do_put(_OutIt _Dest, std::ios_base& _Iosbase, _Elem _Fill, unsigned long long _Val) const
    {
        return col_put(_Dest, _Iosbase, _Fill, _Val);
    }
    virtual _OutIt do_put(_OutIt _Dest, std::ios_base& _Iosbase, _Elem _Fill, float _Val) const
    {
        return col_put(_Dest, _Iosbase, _Fill, _Val);
    }
    virtual _OutIt do_put(_OutIt _Dest, std::ios_base& _Iosbase, _Elem _Fill, double _Val) const
    {
        return col_put(_Dest, _Iosbase, _Fill, _Val);
    }
    virtual _OutIt do_put(_OutIt _Dest, std::ios_base& _Iosbase, _Elem _Fill, long double _Val) const
    {
        return col_put(_Dest, _Iosbase, _Fill, _Val);
    }
};

template< typename _Elem, typename _InIt >
class num_get_interface : public std::num_get< _Elem, _InIt >
{
protected:
    virtual _InIt do_get(_InIt _First, _InIt _Last, std::ios_base& _Iosbase, std::ios_base::iostate& _State, bool& _Val) const = 0;
    virtual _InIt do_get(_InIt _First, _InIt _Last, std::ios_base& _Iosbase, std::ios_base::iostate& _State, char& _Val) const = 0;
    virtual _InIt do_get(_InIt _First, _InIt _Last, std::ios_base& _Iosbase, std::ios_base::iostate& _State, unsigned char& _Val) const = 0;
    virtual _InIt do_get(_InIt _First, _InIt _Last, std::ios_base& _Iosbase, std::ios_base::iostate& _State, short& _Val) const = 0;
    virtual _InIt do_get(_InIt _First, _InIt _Last, std::ios_base& _Iosbase, std::ios_base::iostate& _State, unsigned short& _Val) const = 0;
    virtual _InIt do_get(_InIt _First, _InIt _Last, std::ios_base& _Iosbase, std::ios_base::iostate& _State, int& _Val) const = 0;
    virtual _InIt do_get(_InIt _First, _InIt _Last, std::ios_base& _Iosbase, std::ios_base::iostate& _State, unsigned int& _Val) const = 0;
    virtual _InIt do_get(_InIt _First, _InIt _Last, std::ios_base& _Iosbase, std::ios_base::iostate& _State, long& _Val) const = 0;
    virtual _InIt do_get(_InIt _First, _InIt _Last, std::ios_base& _Iosbase, std::ios_base::iostate& _State, unsigned long& _Val) const = 0;
    virtual _InIt do_get(_InIt _First, _InIt _Last, std::ios_base& _Iosbase, std::ios_base::iostate& _State, long long& _Val) const = 0;
    virtual _InIt do_get(_InIt _First, _InIt _Last, std::ios_base& _Iosbase, std::ios_base::iostate& _State, unsigned long long& _Val) const = 0;
    virtual _InIt do_get(_InIt _First, _InIt _Last, std::ios_base& _Iosbase, std::ios_base::iostate& _State, float& _Val) const = 0;
    virtual _InIt do_get(_InIt _First, _InIt _Last, std::ios_base& _Iosbase, std::ios_base::iostate& _State, double& _Val) const = 0;
    virtual _InIt do_get(_InIt _First, _InIt _Last, std::ios_base& _Iosbase, std::ios_base::iostate& _State, long double& _Val) const = 0;
public:
    template< typename _Vty >
    _InIt get(_InIt _First, _InIt _Last, std::ios_base& _Iosbase, std::ios_base::iostate& _State, _Vty& _Val) const
    {
        return do_get(_First, _Last, _Iosbase, _State, _Val);
    }
};

template< typename _Elem, typename _InIt,
    template< typename _Elem, typename _InIt > class _NgetOper
>
class num_get : public num_get_interface< _Elem, _InIt >
{
private:
    _NgetOper< _Elem, _InIt > op;

    template< typename _Vty >
    _InIt col_get(_InIt _First, _InIt _Last, std::ios_base& _Iosbase, std::ios_base::iostate& _State, _Vty& _Val) const
    {
        return op(_First, _Last, _Iosbase, _State, _Val);
    }
protected:
    virtual _InIt do_get(_InIt _First, _InIt _Last, std::ios_base& _Iosbase, std::ios_base::iostate& _State, bool& _Val) const
    {
        return col_get(_First, _Last, _Iosbase, _State, _Val);
    }
    virtual _InIt do_get(_InIt _First, _InIt _Last, std::ios_base& _Iosbase, std::ios_base::iostate& _State, char& _Val) const
    {
        return col_get(_First, _Last, _Iosbase, _State, _Val);
    }
    virtual _InIt do_get(_InIt _First, _InIt _Last, std::ios_base& _Iosbase, std::ios_base::iostate& _State, unsigned char& _Val) const
    {
        return col_get(_First, _Last, _Iosbase, _State, _Val);
    }
    virtual _InIt do_get(_InIt _First, _InIt _Last, std::ios_base& _Iosbase, std::ios_base::iostate& _State, short& _Val) const
    {
        return col_get(_First, _Last, _Iosbase, _State, _Val);
    }
    virtual _InIt do_get(_InIt _First, _InIt _Last, std::ios_base& _Iosbase, std::ios_base::iostate& _State, unsigned short& _Val) const
    {
        return col_get(_First, _Last, _Iosbase, _State, _Val);
    }
    virtual _InIt do_get(_InIt _First, _InIt _Last, std::ios_base& _Iosbase, std::ios_base::iostate& _State, int& _Val) const
    {
        return col_get(_First, _Last, _Iosbase, _State, _Val);
    }
    virtual _InIt do_get(_InIt _First, _InIt _Last, std::ios_base& _Iosbase, std::ios_base::iostate& _State, unsigned int& _Val) const
    {
        return col_get(_First, _Last, _Iosbase, _State, _Val);
    }
    virtual _InIt do_get(_InIt _First, _InIt _Last, std::ios_base& _Iosbase, std::ios_base::iostate& _State, long& _Val) const
    {
        return col_get(_First, _Last, _Iosbase, _State, _Val);
    }
    virtual _InIt do_get(_InIt _First, _InIt _Last, std::ios_base& _Iosbase, std::ios_base::iostate& _State, unsigned long& _Val) const
    {
        return col_get(_First, _Last, _Iosbase, _State, _Val);
    }
    virtual _InIt do_get(_InIt _First, _InIt _Last, std::ios_base& _Iosbase, std::ios_base::iostate& _State, long long& _Val) const
    {
        return col_get(_First, _Last, _Iosbase, _State, _Val);
    }
    virtual _InIt do_get(_InIt _First, _InIt _Last, std::ios_base& _Iosbase, std::ios_base::iostate& _State, unsigned long long& _Val) const
    {
        return col_get(_First, _Last, _Iosbase, _State, _Val);
    }
    virtual _InIt do_get(_InIt _First, _InIt _Last, std::ios_base& _Iosbase, std::ios_base::iostate& _State, float& _Val) const
    {
        return col_get(_First, _Last, _Iosbase, _State, _Val);
    }
    virtual _InIt do_get(_InIt _First, _InIt _Last, std::ios_base& _Iosbase, std::ios_base::iostate& _State, double& _Val) const
    {
        return col_get(_First, _Last, _Iosbase, _State, _Val);
    }
    virtual _InIt do_get(_InIt _First, _InIt _Last, std::ios_base& _Iosbase, std::ios_base::iostate& _State, long double& _Val) const
    {
        return col_get(_First, _Last, _Iosbase, _State, _Val);
    }
};

#endif
