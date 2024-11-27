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
		size_t		  _Maxidx;
		size_t		  _Mysize;

		_hashtable_imp() : _Bucket_alloc_type(), _Mytable(), _Mysize(0), _Maxidx(1) {
			_Mytable.resize(1);
		}
		_hashtable_imp(const _Bucket_alloc_type& _A) : _Bucket_alloc_type(_A), _Mytable(), _Mysize(0), _Maxidx(1) {
			_Mytable.resize(1);
		}
	};

	_hashtable_imp _Myimp;

	const float _MAX_LOAD = 0.75f;

	float _load() const {
		return static_cast<float>(_Myimp._Mysize) / _Myimp._Mytable.size();
	}

	void _rehash() {
		_Mytable_type new_table(_Myimp._Mytable.size());

		for (auto& bucket : _Myimp._Mytable) {
			for (auto& pair : bucket) {
				size_t hashed_key = iris::XXH64(pair.first) % new_table.size();
				new_table[hashed_key].push_back(pair);
			}
		}

		_Myimp._Mytable = iris::move(new_table);
	}

	void _resize() {
		size_t _new_size = _Myimp._Mytable.size();
		_new_size = _new_size > 1 ? _new_size + (_new_size / 2) : ++_new_size;

		_Myimp._Mytable.resize(_new_size);
		_Myimp._Maxidx = _new_size;
		_rehash();
	}

public:
	using allocator_type = _Al;

	hashtable() : _Myimp() {}
	hashtable(const allocator_type& _A) : _Myimp(_A) {}

public:
	void bucket_insert(const _Mypair_type& _Mypair) {
		if (_load() > _MAX_LOAD) _resize();

		const size_t hashed_key = iris::XXH64(_Mypair.first) % _Myimp._Mytable.size();

		_Mybucket_type& bucket = _Myimp._Mytable[hashed_key];

		for (auto& pair : bucket) {
			if (pair.first == _Mypair.first) {
				pair.second = _Mypair.second;
				return;
			}
		}

		bucket.push_back(_Mypair);
		++_Myimp._Mysize;
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