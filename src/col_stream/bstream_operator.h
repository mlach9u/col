#ifndef __BSTREAM_OPERATOR_H__
#define __BSTREAM_OPERATOR_H__

#include "bstream.h"

#include <vector>
#include <list>
#include <map>

template< typename _Elem, typename _Traits, typename _Alloc >
basic_bostream< _Elem, _Traits >& operator << (basic_bostream< _Elem, _Traits >& _Ostr, const std::basic_string< _Elem, _Traits, _Alloc >& _Str)
{
	_Ostr << (unsigned long)_Str.size() << _Str.c_str();
	return _Ostr;
}

template< typename _Elem, typename _Traits, typename _Alloc >
basic_bistream< _Elem, _Traits >& operator >> (basic_bistream< _Elem, _Traits >& _Istr, std::basic_string< _Elem, _Traits, _Alloc >& _Str)
{
	unsigned long ulSize;

	_Istr >> ulSize;

	_Str.clear();
	_Str.reserve(ulSize);

	typename _Traits::int_type _Meta = _Istr.rdbuf()->sgetc();
	for (; ulSize > 0; --ulSize, _Meta = _Istr.rdbuf()->snextc())
	{
		if (_Traits::eq_int_type(_Traits::eof(), _Meta))
			throw std::exception("End of file");
		else
			_Str.append(1, _Traits::to_char_type(_Meta));
	}

	return _Istr;
}

template< typename _Elem, typename _Traits, typename _Ty >
basic_bostream< _Elem, _Traits >& operator << (basic_bostream< _Elem, _Traits >& _Ostr, const std::vector< _Ty >& _Tys)
{
	unsigned long ulCount = (unsigned long)(_Tys.size());
	_Ostr << ulCount;

	std::vector< _Ty >::const_iterator cit;
	for (cit = _Tys.begin(); cit != _Tys.end(); ++cit)
		_Ostr << *cit;
	return _Ostr;
}

template< typename _Elem, typename _Traits, typename _Ty >
basic_bistream< _Elem, _Traits >& operator >> (basic_bistream< _Elem, _Traits >& _Istr, std::vector< _Ty >& _Tys)
{
	_Tys.clear();

	unsigned long ulCount;
	_Istr >> ulCount;

	_Ty t;
	for (unsigned long i = 0; i < ulCount; i++)
	{
		_Istr >> t;
		_Tys.push_back(t);
	}

	return _Istr;
}

template< typename _Elem, typename _Traits, typename _Ty >
basic_bostream< _Elem, _Traits >& operator << (basic_bostream< _Elem, _Traits >& _Ostr, const std::list< _Ty >& _Tys)
{
	unsigned long ulCount = (unsigned long)(_Tys.size());
	_Ostr << ulCount;

	std::list< _Ty >::const_iterator cit;
	for (cit = _Tys.begin(); cit != _Tys.end(); ++cit)
		_Ostr << *cit;
	return _Ostr;
}

template< typename _Elem, typename _Traits, typename _Ty >
basic_bistream< _Elem, _Traits >& operator >> (basic_bistream< _Elem, _Traits >& _Istr, std::list< _Ty >& _Tys)
{
	_Tys.clear();

	unsigned long ulCount;
	_Istr >> ulCount;

	_Ty t;
	for (unsigned long i = 0; i < ulCount; i++)
	{
		_Istr >> t;
		_Tys.push_back(t);
	}

	return _Istr;
}

template< typename _Elem, typename _Traits, typename _Ty1, typename _Ty2 >
basic_bostream< _Elem, _Traits >& operator << (basic_bostream< _Elem, _Traits >& _Ostr, const std::pair< _Ty1, _Ty2 >& _Pair)
{
	_Ostr << _Pair.first << _Pair.second;
	return _Ostr;
}

template< typename _Elem, typename _Traits, typename _Ty1, typename _Ty2 >
basic_bistream< _Elem, _Traits >& operator << (basic_bistream< _Elem, _Traits >& _Istr, const std::pair< _Ty1, _Ty2 >& _Pair)
{
	_Istr >> _Pair.first >> _Pair.second;
	return _Istr;
}

template< typename _Elem, typename _Traits, typename _Kty, typename _Ty, typename _Pr, typename _Alloc >
basic_bostream< _Elem, _Traits >& operator << (basic_bostream< _Elem, _Traits >& _Ostr, const std::map< _Kty, _Ty, _Pr, _Alloc >& _Map)
{
	unsigned long ulCount = (unsigned long)(_Map.size());
	_Ostr << ulCount;

	std::map< _Kty, _Ty, _Pr, _Alloc >::const_iterator cit;
	for (cit = _Map.begin(); cit != _Map.end(); ++cit)
		_Ostr << *cit;
	return _Ostr;
}

template< typename _Elem, typename _Traits, typename _Kty, typename _Ty, typename _Pr, typename _Alloc >
basic_bistream< _Elem, _Traits >& operator >> (basic_bistream< _Elem, _Traits >& _Istr, std::map< _Kty, _Ty, _Pr, _Alloc >& _Map)
{
	_Map.clear();

	unsigned long ulCount;
	_Istr >> ulCount;

	_Kty k;
	_Ty t;
	for (unsigned long i = 0; i < ulCount; i++)
	{
		_Istr >> k >> t;
		_Map.insert(std::map< _Kty, _Ty, _Pr, _Alloc >::value_type(k, t));
	}

	return _Istr;
}

#endif
