#ifndef _IRIS_EXCEPTION_
#define _IRIS_EXCEPTION_

#include <cxx_config.h>

_IRIS_BEGIN_
class exception {
public:
	exception() throw() {}
	virtual ~exception() throw() {}

	/* Returns a string which describes the cause of the error
	*/
	virtual const char* what() const throw() { return nullptr; }
};
_IRIS_END_

#endif // _EXCEPTION_
