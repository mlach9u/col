#ifndef __BSTREAM_H__
#define __BSTREAM_H__

#include "col_stream.h"

template< typename _Elem, typename _Traits >
std::basic_ostream< _Elem, _Traits >& __cdecl bins(std::basic_ostream< _Elem, _Traits >& _Ostr)
{
	typedef typename basic_ostream< _Elem, _Traits >::_Nput _Nput;
	typedef typename basic_ostream< _Elem, _Traits >::_col_Nput _col_Nput;
	if (dynamic_cast<const _col_Nput*>(&(std::use_facet< _Nput >(_Ostr.getloc()))) == 0)
		_Ostr.imbue(std::locale(_Ostr.getloc(), new _col_Nput));
	_Ostr.iword(__col_stream_index__) = __col_snibinary;
	return _Ostr;
}

template< typename _Elem, typename _Traits >
std::basic_ostream< _Elem, _Traits >& __cdecl nobins(std::basic_ostream< _Elem, _Traits >& _Ostr)
{
	typedef typename basic_ostream< _Elem, _Traits >::_Nput _Nput;
	typedef typename basic_ostream< _Elem, _Traits >::_col_Nput _col_Nput;
	_Ostr.iword(__col_stream_index__) = __col_sninothing;
	if (dynamic_cast<const _col_Nput*>(&(std::use_facet< _Nput >(_Ostr.getloc()))) != 0)
		_Ostr.imbue(std::locale(_Ostr.getloc(), new _Nput));
	return _Ostr;
}

template< typename _Elem, typename _Traits >
std::basic_istream< _Elem, _Traits >& __cdecl bins(std::basic_istream< _Elem, _Traits >& _Ostr)
{
	typedef typename basic_istream< _Elem, _Traits >::_Nget _Nget;
	typedef typename basic_istream< _Elem, _Traits >::_col_Nget _col_Nget;
	if (dynamic_cast<const _col_Nget*>(&(std::use_facet< _Nget >(_Ostr.getloc()))) == 0)
		_Ostr.imbue(std::locale(_Ostr.getloc(), new _col_Nget));
	_Ostr.iword(__col_stream_index__) = __col_snibinary;
	return _Ostr;
}

template< typename _Elem, typename _Traits >
std::basic_istream< _Elem, _Traits >& __cdecl nobins(std::basic_istream< _Elem, _Traits >& _Ostr)
{
	typedef typename basic_istream< _Elem, _Traits >::_Nget _Nget;
	typedef typename basic_istream< _Elem, _Traits >::_col_Nget _col_Nget;
	_Ostr.iword(__col_stream_index__) = __col_sninothing;
	if (dynamic_cast<const _col_Nget*>(&(std::use_facet< _Nget >(_Ostr.getloc()))) != 0)
		_Ostr.imbue(std::locale(_Ostr.getloc(), new _Nget));
	return _Ostr;
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
	{ _Init(_Ptr, _Count, 0); }

	const _Elem* ptr() const
	{
		return _Base::eback();
	}

	size_t size() const
	{
		return ((_Base::pptr() == 0) ? 0 : (_Base::pptr() - _Base::eback()));
	}

	size_t max_size() const
	{
		return ((_Base::epptr() == 0) ? 0 : (_Base::epptr() - _Base::eback()));
	}
};

template< typename _Elem, typename _Traits = std::char_traits< _Elem > >
class basic_bostream : public basic_ostream< _Elem, _Traits >
{
public:
	typedef basic_bostream< _Elem, _Traits > _Myt;
	typedef basic_ostream< _Elem, _Traits > _Base;
	typedef typename _Base::_Mysb _Mysb;

	explicit basic_bostream(_Mysb* _Strbuf)
		: _Base(_Strbuf)
	{
		bins(*this);
	}
};

template< typename _Elem, typename _Traits = std::char_traits< _Elem > >
class basic_bistream : public basic_istream< _Elem, _Traits >
{
public:
	typedef basic_bistream< _Elem, _Traits > _Myt;
	typedef basic_istream< _Elem, _Traits > _Base;
	typedef typename _Base::_Mysb _Mysb;

	explicit basic_bistream(_Mysb* _Strbuf)
		: _Base(_Strbuf)
	{
		bins(*this);
	}
};

typedef basic_binarybuf< char > binarybuf;
typedef basic_bostream< char > bostream;
typedef basic_bistream< char > bistream;

#endif
