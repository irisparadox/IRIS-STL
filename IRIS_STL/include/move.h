#ifndef _IRIS_MOVE_
#define _IRIS_MOVE_

#include <cxx_config.h>
#include <type_traits.h>

_IRIS_BEGIN_
template <typename _Ty>
inline _Ty* __addressof(_Ty& _R) {
	return reinterpret_cast<_Ty*>(&const_cast<char&>(reinterpret_cast<const volatile char&>(_R)));
}

template <typename _Ty>
inline _Ty&& forward(typename IRIS::remove_reference<_Ty>::_Mytype& _Type) {
	return static_cast<_Ty&&>(_Type);
}

template <typename _Ty>
inline _Ty&& forward(typename IRIS::remove_reference<_Ty>::_Mytype&& _Type) {
	static_assert(!IRIS::is_lvalue_reference<_Ty>::value, "template argument substituting _Ty is an lvalue reference type");
	return static_cast<_Ty&&>(_Type);
}
_IRIS_END_
#endif // _IRIS_MOVE_
