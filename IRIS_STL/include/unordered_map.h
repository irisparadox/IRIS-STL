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
	typedef typename _Al::template rebind<iris::list<iris::pair<const _Key, _Val>>>::other _Bucket_alloc_type;
	
	using _Mypair_type = iris::pair<const _Key, _Val>;
	using _Mybucket_type = iris::list<_Mypair_type>;
	using _Mytable_type = iris::vector<_Mybucket_type>;

	struct _hashtable_imp : public _Bucket_alloc_type {
		_Mytable_type _Mytable;

		_hashtable_imp() : _Bucket_alloc_type(), _Mytable() {
			_Mytable.resize(1);
		}
		_hashtable_imp(const _Bucket_alloc_type& _A) : _Bucket_alloc_type(_A), _Mytable() {
			_Mytable.resize(1);
		}
	};

	_hashtable_imp _Myimp;

public:
	using allocator_type = _Al;

	hashtable() : _Myimp() {}
	hashtable(const allocator_type& _A) : _Myimp(_A) {}

public:
	void bucket_insert(const _Mypair_type& _Mypair) {
		const unsigned long long hashed_key = iris::XXH64(_Mypair.first) % _Myimp._Mytable.size();

		if (hashed_key >= _Myimp._Mytable.size()) _Myimp._Mytable.resize(hashed_key + 1);
		_Mybucket_type& bucket = _Myimp._Mytable[hashed_key];

		for (auto& pair : bucket) {
			if (pair.first == _Mypair.first) {
				pair.second = _Mypair.second;
				return;
			}
		}

		bucket.push_back(_Mypair);
	}
};

template <typename _Key, typename _Val, typename _Al = iris::allocator<iris::pair<const _Key,_Val>>>
class unordered_map : protected hashtable<_Key, _Val, _Al> {
	typedef typename _Al::value_type _Myal_value_type;

	typedef hashtable<_Key, _Val, _Al>			 _Mytable;
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