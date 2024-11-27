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
	pair(pair<_U1, _U2>&& _Mypair) : first(iris::forward<_U1>(_Mypair.first)), second(iris::forward<_U2>(_Mypair.second)) {}

	pair& operator=(const pair& _Mypair) {
		first = _Mypair.first;
		second = _Mypair.second;
		return *this;
	}

	pair& operator=(pair&& _Mypair) {
		first = iris::move(_Mypair.first);
		second = iris::move(_Mypair.second);
		return *this;
	}

	template <class _U1, class _U2>
	pair& operator=(const pair<_U1, _U2>& _Mypair) {
		first = _Mypair.first;
		second = _Mypair.second;
		return *this;
	}

	template <class _U1, class _U2>
	pair& operator=(pair<_U1, _U2>&& _Mypair) {
		first = iris::move(_Mypair.first);
		second = iris::move(_Mypair.second);
		return *this;
	}

	void swap(pair& _Mypair) {
		using iris::swap;
		swap(first, _Mypair.first);
		swap(second, _Mypair.second);
	}
#endif // __cplusplus >= __CXX11__
};
	template <class _Ty1, class _Ty2>
	inline _ILIBCXX_CONSTEXPR bool operator==(const pair<_Ty1, _Ty2>& _Left, const pair<_Ty1, _Ty2>& _Right) {
		return _Left.first == _Right.first && _Left.second == _Right.second;
	}

	template <class _Ty1, class _Ty2>
	inline _ILIBCXX_CONSTEXPR bool operator!=(const pair<_Ty1, _Ty2>& _Left, const pair<_Ty1, _Ty2>& _Right) {
		return !(_Left == _Right);
	}

	template <class _Ty1, class _Ty2>
	inline _ILIBCXX_CONSTEXPR bool operator<(const pair<_Ty1, _Ty2>& _Left, const pair<_Ty1, _Ty2>& _Right) {
		return _Left.first < _Right.first || (!(_Right.first < _Left.first) && _Left.second < _Right.second);
	}

	template <class _Ty1, class _Ty2>
	inline _ILIBCXX_CONSTEXPR bool operator>(const pair<_Ty1, _Ty2>& _Left, const pair<_Ty1, _Ty2>& _Right) {
		return _Right < _Left;
	}

	template <class _Ty1, class _Ty2>
	inline _ILIBCXX_CONSTEXPR bool operator<=(const pair<_Ty1, _Ty2>& _Left, const pair<_Ty1, _Ty2>& _Right) {
		return !(_Right < _Left);
	}

	template <class _Ty1, class _Ty2>
	inline _ILIBCXX_CONSTEXPR bool operator>=(const pair<_Ty1, _Ty2>& _Left, const pair<_Ty1, _Ty2>& _Right) {
		return !(_Left < _Right);
	}

#if __CXX_HASCXX0X__
	template <class _Ty1, class _Ty2>
	inline void swap(pair<_Ty1, _Ty2>& _Left, pair<_Ty1, _Ty2>& _Right) {
		_Left.swap(_Right);
	}
#endif
_IRIS_END_
#endif // _IRIS_PAIR_
