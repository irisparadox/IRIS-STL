#ifndef _IRIS_TYPE_TRAITS_
#define _IRIS_TYPE_TRAITS_

#include <cxx_config.h>

_IRIS_BEGIN_

// Integral constant
template <typename _Ty, _Ty _Myval>
struct integral_constant {
	static constexpr _Ty value = _Myval;

	typedef _Ty							   value_type;
	typedef integral_constant<_Ty, _Myval> type;

	constexpr operator value_type() { return value; }
};

typedef integral_constant<bool, true>  true_type;
typedef integral_constant<bool, false> false_type;

// Reference transformations

template <typename>
struct remove_reference;

template <typename _Ty>
struct remove_reference {
	typedef _Ty _Mytype;
};

template <typename _Ty>
struct remove_reference<_Ty&> {
	typedef _Ty _Mytype;
};

template <typename _Ty>
struct remove_reference<_Ty&&> {
	typedef _Ty _Mytype;
};

template <typename>
struct is_lvalue_reference		  : public false_type {};

template <typename _Ty>
struct is_lvalue_reference<_Ty&>  : public true_type  {};

template < typename>
struct is_rvalue_reference        : public false_type {};

template<typename _Tp>
struct is_rvalue_reference<_Tp&&> : public true_type  {};

_IRIS_END_
#endif // _IRIS_TYPE_TRAITS