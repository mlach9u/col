#ifndef __FUNCT_H__
#define __FUNCT_H__

#include "inclusion_funct.h"

template< typename _BinPredLow, typename _BinPredHigh >
struct _range
    : public std::unary_function< typename _BinPredLow::first_argument_type, bool >
{
    typedef std::unary_function< typename _BinPredLow::first_argument_type, bool > _Base;
    typedef typename _Base::argument_type argument_type;

    _range(
        const _BinPredLow& _opl, const typename _BinPredLow::second_argument_type& _vl,
        const _BinPredHigh& _oph, const typename _BinPredHigh::second_argument_type& _vh
    )
        : opl(_opl, _vl), oph(_oph, _vh)
    {
    }

    bool operator()(const argument_type& t) const
    {
        return (opl(t) && oph(t));
    }

    bool operator()(argument_type& t)
    {
        return (opl(t) && oph(t));
    }

public:
    std::binder2nd< _BinPredLow > opl;
    std::binder2nd< _BinPredHigh > oph;
};

template< typename _BinPredLow, typename _BinPredHigh >
inline _range< _BinPredLow, _BinPredHigh > range(
    const _BinPredLow& _opl, const typename _BinPredLow::second_argument_type& _vl,
    const _BinPredHigh& _oph, const typename _BinPredHigh::second_argument_type& _vh
)
{
    return _range< _BinPredLow, _BinPredHigh >(_opl, _vl, _oph, _vh);
}


template< typename _BinOp >
struct _complex_assignment
    : public std::binary_function< typename _BinOp::first_argument_type, typename _BinOp::second_argument_type, typename _BinOp::result_type >
{
    typedef std::binary_function< typename _BinOp::first_argument_type, typename _BinOp::second_argument_type, typename _BinOp::result_type > _Base;
    typedef typename _Base::first_argument_type first_argument_type;
    typedef typename _Base::second_argument_type second_argument_type;
    typedef typename _Base::result_type result_type;

    _complex_assignment(const _BinOp& _Fn)
        : op(_Fn)
    {
    }

    result_type operator()(first_argument_type& _Left, const second_argument_type& _Right) const
    {
        return (_Left = op(_Left, _Right));
    }

public:
    _BinOp op;
};

template< typename _BinOp >
inline _complex_assignment< _BinOp > complex_assignment(
    const _BinOp& _Fn
)
{
    return _complex_assignment< _BinOp >(_Fn);
}


template< typename _UniPred, typename _UniOp >
struct _condition_operator
    : public std::unary_function< typename _UniPred::argument_type, void >
{
    typedef std::unary_function< typename _UniPred::argument_type, void > _Base;
    typedef typename _Base::argument_type argument_type;

    _condition_operator(const _UniPred& _pred, const _UniOp& _op)
        : pred(_pred), op(_op)
    {
    }

    void operator()(argument_type& t)
    {
        if (pred(t))
            op(t);
    }

public:
    _UniPred pred;
    _UniOp op;
};

template< typename _UniPred, typename _UniOp >
inline _condition_operator< _UniPred, _UniOp > condition_operator(
    const _UniPred& _pred, const _UniOp& _op
)
{
    return _condition_operator< _UniPred, _UniOp >(_pred, _op);
}

#endif
