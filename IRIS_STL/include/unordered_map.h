#ifndef _IRIS_UNORDERED_MAP_
#define _IRIS_UNORDERED_MAP_

#include <cxx_config.h>
#include <hashtable.h>
#include <pair.h>

_IRIS_BEGIN_
template <typename _Key, typename _Val, typename _Al = iris::allocator<iris::pair<const _Key,_Val>>>
class unordered_map : protected hashtable<_Key, iris::pair<const _Key, _Val>, _Al, iris::map_key_extract> {
	typedef typename _Al::value_type _Myal_value_type;

	typedef hashtable<_Key, iris::pair<const _Key, _Val>, _Al, iris::map_key_extract>			 _Mytable;
	typedef typename _Mytable::_Bucket_alloc_type _Bucket_alloc_type;

public:
	using key_type        = _Key;
	using value_type      = _Val;
	using key_pointer     = _Key*;
	using key_reference   = _Key&;
	using value_pointer	  = _Val*;
	using value_reference = _Val&;
	using const_key_ptr   = const _Key*;
	using const_key_ref	  = const _Key&;
	using const_value_ptr = const _Val*;
	using const_value_ref = const _Val&;
	using allocator_type  = _Al;

protected:
	using _Mytable::_Myimp;
	using _Mytable::bucket_insert;

public:
	unordered_map() : _Mytable() {}

public:
	void insert(const pair<const _Key, _Val>& _Mypair) {
		_Mytable::bucket_insert(_Mypair);
	}
};
_IRIS_END_
#endif // _IRIS_UNORDERED_MAP_