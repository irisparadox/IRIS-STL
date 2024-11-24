#ifndef _IRIS_ALLOCATOR_
#define _IRIS_ALLOCATOR_

#include <cxx_config.h>
#include <type_traits.h>
#include <exception.h>
#include <mem_operators.h>
#include <move.h>

#define _REDEFINE_NEW_OPERATORS_

_IRIS_BEGIN_

template <typename _Ty>
class allocator {
public:
	using value_type	  = _Ty;
	using size_type		  = size_t;
	using reference		  = _Ty&;
	using const_reference = const _Ty&;
	using pointer		  = _Ty*;
	using const_pointer	  = const _Ty*;

	template<typename _Ty1>
	struct rebind {
		typedef allocator<_Ty1> other;
	};

	allocator() throw() {}
	allocator(const allocator&) throw() {}

	template <typename _Ty1>
	allocator(const allocator<_Ty1>&) throw() {}

	~allocator() throw() {}

public:
	pointer address(reference _Ref) const {
		return IRIS::__addressof(_Ref);
	}

	const_pointer address(const_reference _Ref) const {
		return IRIS::__addressof(_Ref);
	}

	pointer allocate(size_type _N, const void* = 0) {
		if (_N > max_size()) throw IRIS::bad_alloc();

		return static_cast<_Ty*>(::operator new(_N * sizeof(_Ty)));
	}

	void deallocate(pointer _Ptr, size_type) {
		::operator delete(_Ptr);
	}

	size_type max_size() const throw() {
		return size_t(-1) / sizeof(_Ty);
	}

	void construct(pointer _Ptr, const _Ty& _Val) {
		::new((void*)_Ptr) _Ty(_Val);
	}

	template <typename... _Args>
	void construct(pointer _Ptr, _Args&&... _Myargs) {
		::new((void*)_Ptr) _Ty(IRIS::forward<_Args>(_Myargs)...);
	}

	void destroy(pointer _Ptr) {
		_Ptr->~_Ty();
	}
};
_IRIS_END_
#undef _REDEFINE_NEW_OPERATORS_
#endif // _IRIS_ALLOCATOR_
