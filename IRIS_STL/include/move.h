#ifndef _IRIS_MOVE_
#define _IRIS_MOVE_

#include <cxx_config.h>

_IRIS_BEGIN_

#if __CXX_HASCXX0X__

#include <type_traits.h>

template <typename _Ty>
inline _Ty* __addressof(_Ty& _R) {
	return reinterpret_cast<_Ty*>(&const_cast<char&>(reinterpret_cast<const volatile char&>(_R)));
}

template <typename _Ty>
inline _Ty&& forward(typename iris::remove_reference<_Ty>::_Mytype& _Type) {
	return static_cast<_Ty&&>(_Type);
}

template <typename _Ty>
inline _Ty&& forward(typename iris::remove_reference<_Ty>::_Mytype&& _Type) {
	static_assert(!iris::is_lvalue_reference<_Ty>::value, "template argument substituting _Ty is an lvalue reference type");
	return static_cast<_Ty&&>(_Type);
}

template <typename _Ty>
inline typename iris::remove_reference<_Ty>::_Mytype&& move(_Ty&& _Type) {
	return static_cast<typename iris::remove_reference<_Ty>::_Mytype&&>(_Type);
}

#define _ILIBCXX_MOVE(_Val) iris::move(_Val)
#define _ILIBCXX_FORWARD(_Ty, _Val) iris::forward<_Ty>(_Val)
#else
#define _ILIBCXX_MOVE(_Val) (_Val)
#define _ILIBCXX_FORWARD(_Val) (_Val)
#endif // 0X c++ mode

template <typename _Ty>
inline void swap(_Ty& _First, _Ty& _Second) {
	_Ty _tmp = _ILIBCXX_MOVE(_First);
	_First	 = _ILIBCXX_MOVE(_Second);
	_Second  = _ILIBCXX_MOVE(_tmp);
}

template <typename _Ty, size_t _Size>
inline void swap(_Ty(&_First)[_Size], _Ty(&_Second)[_Size]) {
	for (size_t i = 0; i < _Size; ++i) {
		swap(_First[i], _Second[i]);
	}
}
_IRIS_END_
#endif // _IRIS_MOVE_