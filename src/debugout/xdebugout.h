#ifndef __XDEBUGOUT_H__
#define __XDEBUGOUT_H__

#include "inclusion_debugout.h"

template< typename _Elem = char >
struct OutputDebug_Function
{
    typedef char char_type;

    static void dprint(const char_type* lpsz)
    {
        OutputDebugStringA(lpsz);
    }
};

template<>
struct OutputDebug_Function< wchar_t >
{
    typedef wchar_t char_type;

    static void dprint(const char_type* lpsz)
    {
        OutputDebugStringW(lpsz);
    }
};

#endif
