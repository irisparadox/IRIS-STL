#ifndef _IRIS_CXX_CONFIG_
#define _IRIS_CXX_CONFIG_

// Current C++ lib version in ISO date format
#define __ILIBCXX__ 20241122

// Macros for namespacing
//	_IRIS_BEGIN_
//	_IRIS_END_
#define _IRIS_BEGIN_ namespace IRIS {
#define _IRIS_END_ }

_IRIS_BEGIN_
typedef unsigned __int64 size_t;
typedef __int64			 ptrdiff_t;
_IRIS_END_

#endif // _CXX_CONFIG_
