#ifndef __XSTRINGT_H__
#define __XSTRINGT_H__

#include "inclusion_stringt.h"
#include "../col_type_traits/col_type_traits.h"

#ifdef _WINDOWS_
#define __AVOID_STL4017__   // https://devblogs.microsoft.com/cppblog/c17-feature-removals-and-deprecations/
#endif

#ifdef __AVOID_STL4017__
enum CodePageFlag
{
    cpfAutoDetect       = 0x00010000,     // Auto detect UTF-8 or MBCS

    cpfFlagMask         = 0xFFFF0000,
    cpfCodePageMask     = 0x0000FFFF,

    cpfLast = 0
};
#endif

enum CodePageNumber
{
#ifdef __AVOID_STL4017__
    cpnDefault  = (cpfAutoDetect | CP_ACP), // Default code page(CP_ACP) and auto detect whether UTF-8 or not
    cpnANSI     = CP_ACP,                   // Default code page(CP_ACP)
    cpnUTF8     = CP_UTF8,                  // UTF-8 translation(CP_UTF8)
#else
    cpnDefault  = 0,                        // For compatibility
#endif

    cpnLast = 0
};

enum UnicodeNormalizationForm
{
    unfOther,
    unfC, unfD, unfKC, unfKD,

    unfCount
};

struct Function_Base
{
    static size_t col_mbstowcs(wchar_t* lpDst, const char* lpszSrc, size_t cchDstMax, unsigned int nCodePage)
    {
#ifdef __AVOID_STL4017__
        size_t nRet = 0;
        size_t cchSrc = strlen(lpszSrc);
        if (nCodePage & cpfAutoDetect)
        {
            nRet = MultiByteToWideChar(cpnUTF8, MB_ERR_INVALID_CHARS, lpszSrc, (int)cchSrc, lpDst, (int)cchDstMax);
        }

        if (nRet == 0)
        {
            nRet = MultiByteToWideChar(nCodePage & cpfCodePageMask, 0, lpszSrc, (int)cchSrc, lpDst, (int)cchDstMax);
        }
        return ((nRet == 0) ? (size_t)-1 : nRet);
#else
        return mbstowcs(lpDst, lpszSrc, cchDstMax);
#endif
    }

    static size_t col_wcstombs(char* lpDst, const wchar_t* lpszSrc, size_t cchDstMax, unsigned int nCodePage)
    {
#ifdef __AVOID_STL4017__
        size_t nRet = WideCharToMultiByte(nCodePage & cpfCodePageMask, 0, lpszSrc, (int)wcslen(lpszSrc), lpDst, (int)cchDstMax, NULL, NULL);
        return ((nRet == 0) ? (size_t)-1 : nRet);
#else
        return wcstombs(lpDst, lpszSrc, cchDstMax);
#endif
    }

    static bool IsNormalizedString(UnicodeNormalizationForm unf, const wchar_t* lpszString)
    {
#ifdef _WINDOWS_
        return (::IsNormalizedString((NORM_FORM)unf, lpszString, -1) != FALSE);
#else
        return true;
#endif
    }

    static int NormalizeString(UnicodeNormalizationForm unf, const wchar_t* lpszSrc, wchar_t* lpDst, int cchDst)
    {
#ifdef _WINDOWS_
        return ::NormalizeString((NORM_FORM)unf, lpszSrc, -1, lpDst, cchDst);
#else
        return wcslen(lpszSrc);
#endif
    }
};

template< typename _Elem = char >
struct CharType_Function
{
    typedef char _ElemX;
    typedef wchar_t _ElemY;

    static int vsprintf(_ElemX* lpszDst, size_t cchMax, const _ElemX* lpszFormat, va_list args)
    {
        int nRet = vsnprintf(lpszDst, cchMax, lpszFormat, args);
        if ((0 <= nRet) && (cchMax <= (size_t)nRet))
            nRet = -1;
        return nRet;
    }

    static size_t xtoy(_ElemY * lpszDst, const _ElemX * lpszSrc, size_t cchDstMax, unsigned int nCodePage)
    {
        return Function_Base::col_mbstowcs(lpszDst, lpszSrc, cchDstMax, nCodePage);
    }

    static size_t ytox(_ElemX * lpszDst, const _ElemY * lpszSrc, size_t cchDstMax, unsigned int nCodePage)
    {
        return Function_Base::col_wcstombs(lpszDst, lpszSrc, cchDstMax, nCodePage);
    }

    static _ElemX toupper(_ElemX e)
    {
        return (_ElemX)std::toupper((int)e);
    }

    static _ElemX tolower(_ElemX e)
    {
        return (_ElemX)std::tolower((int)e);
    }

    static bool is_normalized(UnicodeNormalizationForm, const _ElemX*)
    {
        return true;
    }

    static int normalize(UnicodeNormalizationForm, const _ElemX* lpszSrc, _ElemX*, int)
    {
        return strlen(lpszSrc);
    }
};

template<>
struct CharType_Function< wchar_t >
{
    typedef wchar_t _ElemX;
    typedef char _ElemY;

    static int vsprintf(_ElemX* lpszDst, size_t cchMax, const _ElemX* lpszFormat, va_list args)
    {
        std::wstring format(lpszFormat);
        std::wstring::size_type start = 0;
        while ((start = format.find_first_of(L'%', start)) != std::wstring::npos)
        {
            start++;
            if (format[start] == L's' || format[start] == L'c')
            {
                format.insert(start, 1, L'l');
            }
        }
        return vswprintf(lpszDst, cchMax, format.c_str(), args);
    }

    static size_t xtoy(_ElemY* lpszDst, const _ElemX* lpszSrc, size_t cchDstMax, unsigned int nCodePage)
    {
        return Function_Base::col_wcstombs(lpszDst, lpszSrc, cchDstMax, nCodePage);
    }

    static size_t ytox(_ElemX* lpszDst, const _ElemY* lpszSrc, size_t cchDstMax, unsigned int nCodePage)
    {
        return Function_Base::col_mbstowcs(lpszDst, lpszSrc, cchDstMax, nCodePage);
    }

    static _ElemX toupper(_ElemX e)
    {
        return (_ElemX)std::towupper((wint_t)e);
    }

    static _ElemX tolower(_ElemX e)
    {
        return (_ElemX)std::towlower((wint_t)e);
    }

    static bool is_normalized(UnicodeNormalizationForm unf, const _ElemX* lpsz)
    {
        return Function_Base::IsNormalizedString(unf, lpsz);
    }

    static int normalize(UnicodeNormalizationForm unf, const _ElemX* lpszSrc, _ElemX* lpDst, int cchDst)
    {
        return Function_Base::NormalizeString(unf, lpszSrc, lpDst, cchDst);
    }
};

template< typename _Elem >
struct CharType_Implement_Base : public CharType_Function< _Elem >
{
    typedef CharType_Function< _Elem > _Base;

    typedef typename _Base::_ElemX _ElemX;
    typedef typename _Base::_ElemY _ElemY;
    typedef std::basic_string< _ElemX > _StrX;
    typedef std::basic_string< _ElemY > _StrY;

    static void _formatV(_StrX& strDst, const _StrX& strFormat, va_list v)
    {
        int nSize, nBufferSize = (int)(strFormat.size() * 2);
        _ElemX* pszBuffer = new _ElemX[nBufferSize];
        va_list _v;
        do
        {
            va_copy(_v, v);
            memset(pszBuffer, 0, nBufferSize * sizeof(_ElemX));
            nSize = _Base::vsprintf(pszBuffer, nBufferSize - 1, strFormat.c_str(), _v);
            if (nSize == -1)
            {
                delete[] pszBuffer;
                nBufferSize *= 2;
                pszBuffer = new _ElemX[nBufferSize];
            }
        } while (nSize == -1);

        strDst = pszBuffer;
        delete[] pszBuffer;
    }

    static void xtoy(_StrY & strDst, const _ElemX * lpszSrc, unsigned int nCodePage)
    {
        size_t cch = _Base::xtoy(NULL, lpszSrc, 0, nCodePage);
        if (cch != (size_t)-1)
        {
            _ElemY* psz = new _ElemY[cch + 1];
            if (_Base::xtoy(psz, lpszSrc, cch + 1, nCodePage) == cch)
            {
                psz[cch] = 0;
                strDst = psz;
            }
            delete[] psz;
        }
    }

    static void xtoy(_StrY & strDst, const _StrX & strSrc, unsigned int nCodePage)
    {
        xtoy(strDst, strSrc.c_str(), nCodePage);
    }

    static void ytox(_StrX & strDst, const _ElemY * lpszSrc, unsigned int nCodePage)
    {
        size_t cch = _Base::ytox(NULL, lpszSrc, 0, nCodePage);
        if (cch != (size_t)-1)
        {
            _ElemX* psz = new _ElemX[cch + 1];
            if (_Base::ytox(psz, lpszSrc, cch + 1, nCodePage) == cch)
            {
                psz[cch] = 0;
                strDst = psz;
            }
            delete[] psz;
        }
    }

    static void ytox(_StrX & strDst, const _StrY & strSrc, unsigned int nCodePage)
    {
        ytox(strDst, strSrc.c_str(), nCodePage);
    }

    static void normalize(_StrX& strDst, const _ElemX* lpszSrc, UnicodeNormalizationForm unf)
    {
        if (!_Base::is_normalized(unf, lpszSrc))
        {
            int cch = _Base::normalize(unf, lpszSrc, 0, 0);
            if (0 < cch)
            {
                _ElemX* psz = new _ElemX[cch + 1];
                if (_Base::normalize(unf, lpszSrc, psz, cch))
                {
                    strDst = psz;
                }
                delete[] psz;
            }
        }
    }
};

#ifndef __STRINGT_UTF8CONVERTER__
#ifndef __AVOID_STL4017__
#ifdef _CODECVT_
#define __STRINGT_UTF8CONVERTER__
typedef std::wstring_convert< std::codecvt_utf8< wchar_t > > utf8converter;
#endif
#endif
#endif

#ifndef __AVOID_STL4017__
#ifndef __STRINGT_UTF8CONVERTER__
#error "UTF-8 converter is not defined."
#endif
#endif

template< typename _Elem = char >
struct CharType_Implement : public CharType_Implement_Base< char >
{
    typedef CharType_Implement_Base< char > _Base;

    typedef _Base::_ElemX _ElemX;
    typedef _Base::_ElemY _ElemY;
    typedef _Base::_StrX _StrX;
    typedef _Base::_StrY _StrY;

    static void xtoutf8(std::string& strDst, const _ElemX* lpszSrc)
    {
        _StrY strY;

        _Base::xtoy(strY, lpszSrc, cpnDefault);
#ifdef __AVOID_STL4017__
        _Base::ytox(strDst, strY, cpnUTF8);
#else
        utf8converter c;
        strDst = c.to_bytes(strY);
#endif
    }

    static void xtoutf8(std::string& strDst, const _StrX& strSrc)
    {
        xtoutf8(strDst, strSrc.c_str());
    }

    static void utf8tox(_StrX& strDst, const char* lpszSrc)
    {
        _StrY strY;

#ifdef __AVOID_STL4017__
        _Base::xtoy(strY, lpszSrc, cpnUTF8);
#else
        utf8converter c;
        strY = c.from_bytes(lpszSrc);
#endif
        _Base::ytox(strDst, strY, cpnDefault);
    }

    static void utf8tox(_StrX& strDst, const std::string& strSrc)
    {
        utf8tox(strDst, strSrc.c_str());
    }
};

template<>
struct CharType_Implement< wchar_t > : public CharType_Implement_Base< wchar_t >
{
    typedef CharType_Implement_Base< wchar_t > _Base;

    typedef _Base::_ElemX _ElemX;
    typedef _Base::_ElemY _ElemY;
    typedef _Base::_StrX _StrX;
    typedef _Base::_StrY _StrY;

    static void xtoutf8(std::string& strDst, const _ElemX* lpszSrc)
    {
#ifdef __AVOID_STL4017__
        _Base::xtoy(strDst, lpszSrc, cpnUTF8);
#else
        utf8converter c;
        strDst = c.to_bytes(lpszSrc);
#endif
    }

    static void xtoutf8(std::string& strDst, const _StrX& strSrc)
    {
        xtoutf8(strDst, strSrc.c_str());
    }

    static void utf8tox(_StrX& strDst, const char* lpszSrc)
    {
#ifdef __AVOID_STL4017__
        _Base::ytox(strDst, lpszSrc, cpnUTF8);
#else
        utf8converter c;
        strDst = c.from_bytes(lpszSrc);
#endif
    }

    static void utf8tox(_StrX& strDst, const std::string& strSrc)
    {
        utf8tox(strDst, strSrc.c_str());
    }
};

#endif
