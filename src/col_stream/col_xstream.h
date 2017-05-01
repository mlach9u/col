#ifndef __COL_XSTREAM_H__
#define __COL_XSTREAM_H__

#include "inclusion_col_stream.h"
#include "..\\col_type_traits\\col_type_traits.h"

enum __col_stream_number_index__
{
	__col_sninothing = 0,
	__col_snibinary,
	__col_snicount
};

int __col_stream_index__ = std::ios_base::xalloc();

template< typename _Elem, typename _OutIt = std::ostreambuf_iterator< _Elem, std::char_traits< _Elem > > >
class num_put : public std::num_put< _Elem, _OutIt >
{
private:
	template< typename _Vty >
	_OutIt bin_put(_OutIt _Dest, _Vty _Val) const
	{
		int _Cch = (sizeof(_Vty) / sizeof(_Elem)) + (sizeof(_Vty) % sizeof(_Elem));
		_Elem _Buff[(sizeof(_Vty) / sizeof(_Elem)) + (sizeof(_Vty) % sizeof(_Elem))];
		memset(_Buff, 0, _Cch * sizeof(_Elem));
		memcpy(_Buff, &_Val, sizeof(_Vty));
		for (int i = 0; i < _Cch; i++, _Dest++)
			*_Dest = _Buff[i];
		return _Dest;
	}
	template< typename _Vty >
	_OutIt col_put(_OutIt _Dest, std::ios_base& _Iosbase, _Elem _Fill, _Vty _Val) const
	{
		switch (_Iosbase.iword(__col_stream_index__))
		{
		case __col_snibinary:	return bin_put(_Dest, _Val);
		}
		return (*_OutIt(0) = _Elem());
	}
protected:
	virtual _OutIt do_put(_OutIt _Dest, std::ios_base& _Iosbase, _Elem _Fill, bool _Val) const
	{ return col_put(_Dest, _Iosbase, _Fill, _Val); }
	virtual _OutIt do_put(_OutIt _Dest, std::ios_base& _Iosbase, _Elem _Fill, char _Val) const
	{ return col_put(_Dest, _Iosbase, _Fill, _Val); }
	virtual _OutIt do_put(_OutIt _Dest, std::ios_base& _Iosbase, _Elem _Fill, unsigned char _Val) const
	{ return col_put(_Dest, _Iosbase, _Fill, _Val); }
	virtual _OutIt do_put(_OutIt _Dest, std::ios_base& _Iosbase, _Elem _Fill, short _Val) const
	{ return col_put(_Dest, _Iosbase, _Fill, _Val); }
	virtual _OutIt do_put(_OutIt _Dest, std::ios_base& _Iosbase, _Elem _Fill, unsigned short _Val) const
	{ return col_put(_Dest, _Iosbase, _Fill, _Val); }
	virtual _OutIt do_put(_OutIt _Dest, std::ios_base& _Iosbase, _Elem _Fill, int _Val) const
	{ return col_put(_Dest, _Iosbase, _Fill, _Val); }
	virtual _OutIt do_put(_OutIt _Dest, std::ios_base& _Iosbase, _Elem _Fill, unsigned int _Val) const
	{ return col_put(_Dest, _Iosbase, _Fill, _Val); }
	virtual _OutIt do_put(_OutIt _Dest, std::ios_base& _Iosbase, _Elem _Fill, long _Val) const
	{ return col_put(_Dest, _Iosbase, _Fill, _Val); }
	virtual _OutIt do_put(_OutIt _Dest, std::ios_base& _Iosbase, _Elem _Fill, unsigned long _Val) const
	{ return col_put(_Dest, _Iosbase, _Fill, _Val); }
	virtual _OutIt do_put(_OutIt _Dest, std::ios_base& _Iosbase, _Elem _Fill, long long _Val) const
	{ return col_put(_Dest, _Iosbase, _Fill, _Val); }
	virtual _OutIt do_put(_OutIt _Dest, std::ios_base& _Iosbase, _Elem _Fill, unsigned long long _Val) const
	{ return col_put(_Dest, _Iosbase, _Fill, _Val); }
	virtual _OutIt do_put(_OutIt _Dest, std::ios_base& _Iosbase, _Elem _Fill, float _Val) const
	{ return col_put(_Dest, _Iosbase, _Fill, _Val); }
	virtual _OutIt do_put(_OutIt _Dest, std::ios_base& _Iosbase, _Elem _Fill, double _Val) const
	{ return col_put(_Dest, _Iosbase, _Fill, _Val); }
	virtual _OutIt do_put(_OutIt _Dest, std::ios_base& _Iosbase, _Elem _Fill, long double _Val) const
	{ return col_put(_Dest, _Iosbase, _Fill, _Val); }
public:
	template< typename _Vty >
	_OutIt put(_OutIt _Dest, std::ios_base& _Iosbase, _Elem _Fill, _Vty _Val) const
	{ return do_put(_Dest, _Iosbase, _Fill, _Val); }
};

template< typename _Elem, typename _InIt = std::istreambuf_iterator<_Elem, std::char_traits<_Elem> > >
class num_get : public std::num_get< _Elem, _InIt >
{
private:
	template< typename _Vty >
	_InIt bin_get(_InIt _First, _InIt _Last, std::ios_base::iostate& _State, _Vty& _Val) const
	{
		int _Cch = (sizeof(_Vty) / sizeof(_Elem)) + (sizeof(_Vty) % sizeof(_Elem));
		_Elem _Buff[(sizeof(_Vty) / sizeof(_Elem)) + (sizeof(_Vty) % sizeof(_Elem))];
		for (int i = 0; (i < _Cch) && (_First != _Last); i++, _First++)
			_Buff[i] = *_First;
		if (_First == _Last)
		{
			_State |= std::ios_base::eofbit;
			memset(&_Buff[i], _Elem(), ((_Cch - i) * sizeof(_Elem)));
		}
		memcpy(&_Val, _Buff, sizeof(_Vty));
		return _First;
	}
	template< typename _Vty >
	_InIt col_get(_InIt _First, _InIt _Last, std::ios_base& _Iosbase, std::ios_base::iostate& _State, _Vty& _Val) const
	{
		switch (_Iosbase.iword(__col_stream_index__))
		{
		case __col_snibinary:	return bin_get(_First, _Last, _State, _Val);
		}
		return _InIt(0);
	}
protected:
	virtual _InIt do_get(_InIt _First, _InIt _Last, std::ios_base& _Iosbase, std::ios_base::iostate& _State, bool& _Val) const
	{ return col_get(_First, _Last, _Iosbase, _State, _Val); }
	virtual _InIt do_get(_InIt _First, _InIt _Last, std::ios_base& _Iosbase, std::ios_base::iostate& _State, char& _Val) const
	{ return col_get(_First, _Last, _Iosbase, _State, _Val); }
	virtual _InIt do_get(_InIt _First, _InIt _Last, std::ios_base& _Iosbase, std::ios_base::iostate& _State, unsigned char& _Val) const
	{ return col_get(_First, _Last, _Iosbase, _State, _Val); }
	virtual _InIt do_get(_InIt _First, _InIt _Last, std::ios_base& _Iosbase, std::ios_base::iostate& _State, short& _Val) const
	{ return col_get(_First, _Last, _Iosbase, _State, _Val); }
	virtual _InIt do_get(_InIt _First, _InIt _Last, std::ios_base& _Iosbase, std::ios_base::iostate& _State, unsigned short& _Val) const
	{ return col_get(_First, _Last, _Iosbase, _State, _Val); }
	virtual _InIt do_get(_InIt _First, _InIt _Last, std::ios_base& _Iosbase, std::ios_base::iostate& _State, int& _Val) const
	{ return col_get(_First, _Last, _Iosbase, _State, _Val); }
	virtual _InIt do_get(_InIt _First, _InIt _Last, std::ios_base& _Iosbase, std::ios_base::iostate& _State, unsigned int& _Val) const
	{ return col_get(_First, _Last, _Iosbase, _State, _Val); }
	virtual _InIt do_get(_InIt _First, _InIt _Last, std::ios_base& _Iosbase, std::ios_base::iostate& _State, long& _Val) const
	{ return col_get(_First, _Last, _Iosbase, _State, _Val); }
	virtual _InIt do_get(_InIt _First, _InIt _Last, std::ios_base& _Iosbase, std::ios_base::iostate& _State, unsigned long& _Val) const
	{ return col_get(_First, _Last, _Iosbase, _State, _Val); }
	virtual _InIt do_get(_InIt _First, _InIt _Last, std::ios_base& _Iosbase, std::ios_base::iostate& _State, long long& _Val) const
	{ return col_get(_First, _Last, _Iosbase, _State, _Val); }
	virtual _InIt do_get(_InIt _First, _InIt _Last, std::ios_base& _Iosbase, std::ios_base::iostate& _State, unsigned long long& _Val) const
	{ return col_get(_First, _Last, _Iosbase, _State, _Val); }
	virtual _InIt do_get(_InIt _First, _InIt _Last, std::ios_base& _Iosbase, std::ios_base::iostate& _State, float& _Val) const
	{ return col_get(_First, _Last, _Iosbase, _State, _Val); }
	virtual _InIt do_get(_InIt _First, _InIt _Last, std::ios_base& _Iosbase, std::ios_base::iostate& _State, double& _Val) const
	{ return col_get(_First, _Last, _Iosbase, _State, _Val); }
	virtual _InIt do_get(_InIt _First, _InIt _Last, std::ios_base& _Iosbase, std::ios_base::iostate& _State, long double& _Val) const
	{ return col_get(_First, _Last, _Iosbase, _State, _Val); }
public:
	template< typename _Vty >
	_InIt get(_InIt _First, _InIt _Last, std::ios_base& _Iosbase, std::ios_base::iostate& _State, _Vty& _Val) const
	{ return do_get(_First, _Last, _Iosbase, _State, _Val); }
};

#endif
