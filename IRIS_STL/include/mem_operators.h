#ifndef _IRIS_MEM_OPERATORS_
#define _IRIS_MEM_OPERATORS_

#include <cxx_config.h>
#include <exception.h>

_IRIS_BEGIN_

/**
*	@brief Exception probably thrown by @c new.
*	@ingroup exceptions
* 
*	@c bad_alloc is used to throw exceptions when allocating using @c new.
*/
class bad_alloc : public exception {
public:
	bad_alloc() throw() {}
	~bad_alloc() throw() {}
	
	const char* what() const throw() { return "bad memory alloc"; }
};
_IRIS_END_

#ifdef _REDEFINE_NEW_OPERATORS_
#if __cplusplus < __CXX17__
	void* operator new(iris::size_t) throw(iris::bad_alloc);
	void* operator new[](iris::size_t) throw(iris::bad_alloc);
#else
	void* operator new(iris::size_t) noexcept(false);
	void* operator new[](iris::size_t) noexcept(false);
#endif

void  operator delete(void*) throw();
void  operator delete[](void*) throw();

// Default versions of new
inline void* operator new(iris::size_t, void* _Ptr) throw() { return _Ptr; }
inline void* operator new[](iris::size_t, void* _Ptr) throw() { return _Ptr; }

// Default versions of delete
inline void  operator delete(void*, void*) throw() { }
inline void  operator delete[](void*, void*) throw() { }
#endif // _REDEFINE_NEW_OPERATORS_

#endif // _IRIS_MEM_OPERATORS_
