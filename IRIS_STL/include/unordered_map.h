#ifndef _IRIS_UNORDERED_MAP_
#define _IRIS_UNORDERED_MAP_

#include <cxx_config.h>
#include <list.h>
#include <vector.h>
#include <pair.h>
#include <hash.h>

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

public:

	hashtable() : _Myimp() {}
};

template <typename _Key, typename _Val, typename _Al = IRIS::allocator<IRIS::pair<_Key,_Val>>>
class unordered_map : protected hashtable<_Key, _Val, _Al> {
	typedef typename _Al::value_type _Myal_value_type;

	typedef hashtable<_Key, _Val, _Al>			 _Mybase;
	typedef typename _Mybase::_Bucket_alloc_type _Bucket_alloc_type;

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
	using _Mybase::_Myimp;

public:
	unordered_map() : _Mybase() {}
};
_IRIS_END_
#endif // _IRIS_UNORDERED_MAP_