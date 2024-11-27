#ifndef _IRIS_UNORDERED_MAP_
#define _IRIS_UNORDERED_MAP_

#include <cxx_config.h>
#include <list.h>
#include <vector.h>
#include <pair.h>

_IRIS_BEGIN_
template <typename _Key, typename _Val, typename _Al>
class hashtable {
protected:
	typedef typename _Al::template rebind<IRIS::list<IRIS::pair<_Key, _Val>>>::other _Bucket_alloc_type;
	
	using _Mypair_type = IRIS::pair<_Key, _Val>;
	using _Mybucket_type = IRIS::list<_Mypair_type>;
	using _Mytable_type = IRIS::vector<_Mybucket_type>;

	struct _hashtable_imp : public _Bucket_alloc_type {
		_Mytable_type _Mytable;

		_hashtable_imp() : _Bucket_alloc_type(), _Mytable() {}
		_hashtable_imp(const _Bucket_alloc_type& _A) : _Bucket_alloc_type(_A), _Mytable() {}
	};

	_hashtable_imp _Myimp;
};
_IRIS_END_
#endif // _IRIS_UNORDERED_MAP_