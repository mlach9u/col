#ifndef __XSTRINGT_H__
#define __XSTRINGT_H__

#include "inclusion_stringt.h"

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

	static size_t xtoy(_ElemY* lpszDst, const _ElemX* lpszSrc, size_t cchDstMax)
	{
		return mbstowcs(lpszDst, lpszSrc, cchDstMax);
	}

	static size_t ytox(_ElemX* lpszDst, const _ElemY* lpszSrc, size_t cchDstMax)
	{
		return wcstombs(lpszDst, lpszSrc, cchDstMax);
	}
};

template<>
struct CharType_Function< wchar_t >
{
	typedef wchar_t _ElemX;
	typedef char _ElemY;

	static int vsprintf(_ElemX* lpszDst, size_t cchMax, const _ElemX* lpszFormat, va_list args)
	{
		return vswprintf(lpszDst, cchMax, lpszFormat, args);
	}

	static size_t xtoy(_ElemY* lpszDst, const _ElemX* lpszSrc, size_t cchDstMax)
	{
		return wcstombs(lpszDst, lpszSrc, cchDstMax);
	}

	static size_t ytox(_ElemX* lpszDst, const _ElemY* lpszSrc, size_t cchDstMax)
	{
		return mbstowcs(lpszDst, lpszSrc, cchDstMax);
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
		do
		{
			memset(pszBuffer, 0, nBufferSize * sizeof(_ElemX));
			nSize = _Base::vsprintf(pszBuffer, nBufferSize - 1, strFormat.c_str(), v);
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

	static void xtoy(_StrY& strDst, const _ElemX* lpszSrc)
	{
		size_t cch = _Base::xtoy(NULL, lpszSrc, 0);
		if (cch != (size_t)-1)
		{
			_ElemY* psz = new _ElemY[cch + 1];
			if (_Base::xtoy(psz, lpszSrc, cch + 1) == cch)
			{
				psz[cch] = 0;
				strDst = psz;
			}
			delete[] psz;
		}
	}

	static void xtoy(_StrY& strDst, const _StrX& strSrc)
	{
		xtoy(strDst, strSrc.c_str());
	}

	static void ytox(_StrX& strDst, const _ElemY* lpszSrc)
	{
		size_t cch = _Base::ytox(NULL, lpszSrc, 0);
		if (cch != (size_t)-1)
		{
			_ElemX* psz = new _ElemX[cch + 1];
			if (_Base::ytox(psz, lpszSrc, cch + 1) == cch)
			{
				psz[cch] = 0;
				strDst = psz;
			}
			delete[] psz;
		}
	}

	static void ytox(_StrX& strDst, const _StrY& strSrc)
	{
		ytox(strDst, strSrc.c_str());
	}
};

#ifndef __STRINGT_UTF8CONVERTER__
#ifdef _CODECVT_
#define __STRINGT_UTF8CONVERTER__
typedef std::wstring_convert< std::codecvt_utf8< wchar_t > > utf8converter;
#endif
#endif

#ifndef __STRINGT_UTF8CONVERTER__
#ifdef _WINDOWS_
#define __STRINGT_UTF8CONVERTER__
struct utf8converter
{
	std::string to_bytes(const wchar_t* lpsz)
	{
		return to_bytes(lpsz, wcslen(lpsz));
	}

	std::string to_bytes(const std::wstring& str)
	{
		return to_bytes(str.c_str(), str.size());
	}

	std::string to_bytes(const wchar_t* lpszFirst, const wchar_t* lpszLast)
	{
		return to_bytes(lpszFirst, (lpszLast - lpszFirst) / sizeof(wchar_t));
	}

	std::string to_bytes(const wchar_t* lpszFirst, size_t cch)
	{
		std::string strRet;
		int cchUtf8 = WideCharToMultiByte(CP_UTF8, 0, lpszFirst, cch, NULL, 0, NULL, NULL);
		if (cchUtf8 != 0)
		{
			char* pszUtf8 = new char[cchUtf8 + 1];
			if (WideCharToMultiByte(CP_UTF8, 0, lpszFirst, cch, pszUtf8, cchUtf8, NULL, NULL) == cchUtf8)
			{
				pszUtf8[cchUtf8] = 0;
				strRet = pszUtf8;
			}
			delete[] pszUtf8;
		}
		return strRet;
	}

	std::wstring from_bytes(const char* lpsz)
	{
		return from_bytes(lpsz, strlen(lpsz));
	}

	std::wstring from_bytes(const std::string& str)
	{
		return from_bytes(str.c_str(), str.size());
	}

	std::wstring from_bytes(const char* lpszFirst, const char* lpszLast)
	{
		return from_bytes(lpszFirst, (lpszLast - lpszFirst) / sizeof(char));
	}

	std::wstring from_bytes(const char* lpszFirst, size_t cch)
	{
		std::wstring strRet;
		int cchWideChar = MultiByteToWideChar(CP_UTF8, 0, lpszFirst, cch, NULL, 0);
		if (cchWideChar != 0)
		{
			wchar_t* pszWideChar = new wchar_t[cchWideChar + 1];
			if (MultiByteToWideChar(CP_UTF8, 0, lpszFirst, cch, pszWideChar, cchWideChar) == cchWideChar)
			{
				pszWideChar[cchWideChar] = 0;
				strRet = pszWideChar;
			}
			delete[] pszWideChar;
		}
		return strRet;
	}
};
#endif
#endif

#ifndef __STRINGT_UTF8CONVERTER__
#error "UTF-8 converter is not defined."
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

		utf8converter c;
		_Base::xtoy(strY, lpszSrc);
		strDst = c.to_bytes(strY);
	}

	static void xtoutf8(std::string& strDst, const _StrX& strSrc)
	{
		xtoutf8(strDst, strSrc.c_str());
	}

	static void utf8tox(_StrX& strDst, const char* lpszSrc)
	{
		_StrY strY;

		utf8converter c;
		strY = c.from_bytes(lpszSrc);
		_Base::ytox(strDst, strY);
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
		utf8converter c;
		strDst = c.to_bytes(lpszSrc);
	}

	static void xtoutf8(std::string& strDst, const _StrX& strSrc)
	{
		xtoutf8(strDst, strSrc.c_str());
	}

	static void utf8tox(_StrX& strDst, const char* lpszSrc)
	{
		utf8converter c;
		strDst = c.from_bytes(lpszSrc);
	}

	static void utf8tox(_StrX& strDst, const std::string& strSrc)
	{
		utf8tox(strDst, strSrc.c_str());
	}
};

#endif
