#ifndef _IRIS_CXX_CONFIG_
#define _IRIS_CXX_CONFIG_

// Current C++ lib version in ISO date format
#define __ILIBCXX__ 20241122

// CPLUSPLUS VERSIONS
#define __CXX98__ 199711L // C++98/03
#define __CXX11__ 201103L // C++11
#define __CXX14__ 201402L // C++14
#define __CXX17__ 201703L // C++17
#define __CXX20__ 202002L // C++20
#define __CXX23__ 202302L // C++23

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
