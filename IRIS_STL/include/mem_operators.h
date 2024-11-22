#ifndef _IRIS_MEM_OPERATORS_
#define _IRIS_MEM_OPERATORS_

#include <cxx_config.h>
#include <exception.h>

_IRIS_BEGIN_
class bad_alloc : public exception {
public:
	bad_alloc() throw() {}
	~bad_alloc() throw() {}
	
	const char* what() const throw() { return "bad memory alloc"; }
};
_IRIS_END_

void* operator new(IRIS::size_t) throw(IRIS::bad_alloc);
void* operator new[](IRIS::size_t) throw(IRIS::bad_alloc);
void  operator delete(void*) throw();
void  operator delete[](void*) throw();

// Default versions of new
inline void* operator new(IRIS::size_t, void* _Ptr) throw() { return _Ptr; }
inline void* operator new[](IRIS::size_t, void* _Ptr) throw() { return _Ptr; }

// Default versions of delete
inline void  operator delete(void*, void*) throw() { }
inline void  operator delete[](void*, void*) throw() { }

#endif // _IRIS_MEM_OPERATORS_
