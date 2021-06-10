#ifndef __TVALUE_H__
#define __TVALUE_H__

#include "inclusion_tvalue.h"
#include "../col_type_traits/col_type_traits.h"

struct tvalue_data_root
{
    virtual ~tvalue_data_root() {}
};

typedef std::shared_ptr< tvalue_data_root > tvalue_data_ptr;

template<typename _ValueType>
struct tvalue_data : public tvalue_data_root, public _ValueType
{
    typedef tvalue_data<_ValueType> _Myt;

    tvalue_data() {}
    tvalue_data(const _ValueType& v) : _ValueType(v) {}
    virtual ~tvalue_data() {}
    const _Myt& operator = (const _ValueType& _Other) { (_ValueType&)(*this) = _Other; return *this; }
};

template<typename _ValueType>
struct tvalue_default_data_base
{
    typedef tvalue_default_data_base<_ValueType> _Myt;

    virtual void get(_ValueType& v) const = 0;
    operator _ValueType() const { _ValueType v; get(v); return v; }
};

template<typename _ValueType>
struct tvalue_default_data : public tvalue_data_root,
    public tvalue_default_data_base<bool>,
    public tvalue_default_data_base<char>, public tvalue_default_data_base<unsigned char>,
    public tvalue_default_data_base<short>, public tvalue_default_data_base<unsigned short>,
    public tvalue_default_data_base<int>, public tvalue_default_data_base<unsigned int>,
    public tvalue_default_data_base<long>, public tvalue_default_data_base<unsigned long>,
    public tvalue_default_data_base<long long>, public tvalue_default_data_base<unsigned long long>,
    public tvalue_default_data_base<float>, public tvalue_default_data_base<double>, public tvalue_default_data_base<long double>
{
    typedef tvalue_default_data<_ValueType> _Myt;

    tvalue_default_data() {}
    tvalue_default_data(const _ValueType& v) : m_v(v) {}
    virtual ~tvalue_default_data() {}

    const _Myt& operator = (_ValueType v) { m_v = v; return *this; }

    virtual void get(bool& v) const { v = (m_v != 0); }
    virtual void get(char& v) const { v = (char)m_v; }
    virtual void get(unsigned char& v) const { v = (unsigned char)m_v; }
    virtual void get(short& v) const { v = (short)m_v; }
    virtual void get(unsigned short& v) const { v = (unsigned short)m_v; }
    virtual void get(int& v) const { v = (int)m_v; }
    virtual void get(unsigned int& v) const { v = (unsigned int)m_v; }
    virtual void get(long& v) const { v = (long)m_v; }
    virtual void get(unsigned long& v) const { v = (unsigned long)m_v; }
    virtual void get(long long& v) const { v = (long long)m_v; }
    virtual void get(unsigned long long& v) const { v = (unsigned long long)m_v; }
    virtual void get(float& v) const { v = (float)m_v; }
    virtual void get(double& v) const { v = (double)m_v; }
    virtual void get(long double& v) const { v = (long double)m_v; }

private:
    _ValueType m_v;
};

struct tvalue
{
    typedef tvalue _Myt;

    template<typename _Ty>
    typename std::enable_if<is_default<_Ty>::value, const _Myt>::type&
    operator = (const _Ty& v) { return set_default(v); }

    template<typename _Ty>
    typename std::enable_if<!is_default<_Ty>::value, const _Myt>::type&
    operator = (const _Ty& v) { return set_define(v); }

    template<typename _Elem> const _Myt& operator = (_Elem* v)
    {
        typedef typename std::remove_cv<_Elem>::type type;
        static_assert(is_char<type>::value, "_Elem must be character type");
        return set_define(std::basic_string<type>(v));
    }

    template<typename _Ty> operator _Ty() const { return as<_Ty>(); }

    template<typename _Ty, typename _Rt = typename remove_cv<typename remove_reference<_Ty>::type>::type>
    typename std::enable_if<is_default<_Ty>::value && !is_pointer<_Ty>::value, _Ty>::type
    as() const
    {
        throwalloc();
        return dynamic_cast<const tvalue_default_data_base<_Rt>&>(*m_pdata);
    }

    template<typename _Ty, typename _Rt = typename remove_cv<typename remove_pointer<_Ty>::type>::type>
    typename std::enable_if<is_default<typename remove_pointer<_Ty>::type>::value && is_pointer<_Ty>::value, _Ty>::type
    as() const
    {
        static_assert(!is_char<_Ty>::value, "_Ty must be character type");
        throwalloc();
        return dynamic_cast<const tvalue_data<std::basic_string<_Rt>>&>(*m_pdata).c_str();
    }

    template<typename _Ty, typename _Rt = typename remove_cv<typename remove_reference<_Ty>::type>::type>
    typename std::enable_if<!is_default<_Ty>::value && !is_pointer<_Ty>::value, _Ty>::type
    as() const
    {
        throwalloc();
        return dynamic_cast<const tvalue_data<_Rt>&>(*m_pdata);
    }

private:
    void throwalloc() const { if (m_pdata.get() == nullptr) throw std::bad_alloc(); }

    template<typename _DataCont, typename _Ty>
    const _Myt& set(const _Ty & v)
    {
        try { throwalloc();	(dynamic_cast<_DataCont&>(*m_pdata)) = v; }
        catch (...) { m_pdata.reset(new _DataCont(v)); }
        return *this;
    }

    template<typename _Ty> const _Myt& set_define(const _Ty & v)
    {
        return set<tvalue_data<_Ty>, _Ty>(v);
    }

    template<typename _Ty> const _Myt& set_default(const _Ty& v)
    {
        return set<tvalue_default_data<_Ty>, _Ty>(v);
    }

    tvalue_data_ptr m_pdata;
};

#endif
