#ifndef _IRIS_PAIR_
#define _IRIS_PAIR_

#include <cxx_config.h>
#include <move.h>

_IRIS_BEGIN_

template <class _Ty1, class _Ty2>
struct pair {
	typedef _Ty1 _Left_type;
	typedef _Ty2 _Right_type;

	_Ty1 first;
	_Ty2 second;

	_ILIBCXX_CONSTEXPR pair() : first(), second() {}
	_ILIBCXX_CONSTEXPR pair(const _Ty1& _Left, const _Ty2& _Right) : first(_Left), second(_Right) {}

	template <class _U1, class _U2>
	_ILIBCXX_CONSTEXPR pair(const pair<_U1, _U2>& _Mypair) : first(_Mypair.first), second(_Mypair.second) {}

#if __CXX_HASCXX0X__
	constexpr pair(const pair&) = default;

	template <class _U1, class _U2>
	pair(pair<_U1, _U2>&& _Mypair) : first(IRIS::forward<_U1>(_Mypair.first)), second(IRIS::forward<_U2>(_Mypair.second)) {}
#endif // __cplusplus >= __CXX11__

};
_IRIS_END_
#endif // _IRIS_PAIR_
