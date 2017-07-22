#ifndef __DEBUGOUT_H__
#define __DEBUGOUT_H__

#include "xdebugout.h"

template< typename _Elem, typename _Traits, typename _Alloc >
class basic_debugbuf : public std::basic_stringbuf< _Elem, _Traits, _Alloc >
{
public:
	typedef std::basic_stringbuf<_Elem, _Traits, _Alloc > _Base;

	typedef typename _Base::int_type int_type;

	typedef OutputDebug_Function< _Elem > _Function;

	basic_debugbuf() : _Base(std::ios_base::out) {}
	virtual ~basic_debugbuf() {}

protected:
	virtual int_type overflow(int_type _Meta = _Traits::eof())
	{
		int_type nRet = _Base::overflow(_Meta);
		if (true
			&& (!(_Traits::eq_int_type(_Traits::eof(), nRet)))
			&& (_Traits::eq_int_type(int_type('\n'), _Meta))
			)
			sync();
		return nRet;
	}

	virtual int sync()
	{
		_Function::dprint(str().c_str());
		_Tidy();
		return _Base::sync();
	}
};

template< typename _Elem, typename _Traits = std::char_traits< _Elem >, typename _Alloc = std::allocator< _Elem > >
class basic_odebugstream : public std::basic_ostream< _Elem, _Traits >
{
public:
	typedef std::basic_ostream< _Elem, _Traits > _Base;
	typedef basic_debugbuf< _Elem, _Traits, _Alloc > _Buffer;

	basic_odebugstream()
		: _Base(&_Stringbuffer)
		, _Stringbuffer()
	{}

	virtual ~basic_odebugstream()
	{}

private:
	_Buffer _Stringbuffer;
};

typedef basic_odebugstream< char > dstream;
typedef basic_odebugstream< wchar_t > wdstream;

#endif
