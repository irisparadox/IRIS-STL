#ifndef _IRIS_HASHTABLE_
#define _IRIS_HASHTABLE_

#include <cxx_config.h>
#include <list.h>
#include <vector.h>
#include <hash.h>
#include <key_extractor.h>
#include <hashtable_traits.h>

_IRIS_BEGIN_
template <typename _Key, typename _Val, typename _Al, typename _ExtractKey>
class hashtable {
protected:
	typedef typename _Al::template rebind<iris::list<_Val>>::other _Bucket_alloc_type;

	using value_type = _Val;
	using _Mybucket_type = iris::list<value_type>;
	using _Mytable_type = iris::vector<_Mybucket_type>;

	struct _hashtable_imp : public _Bucket_alloc_type {
		_Mytable_type _Mytable;
		size_t		  _Maxidx;
		size_t		  _Mysize;

		_hashtable_imp() : _Bucket_alloc_type(), _Mytable(1), _Mysize(0), _Maxidx(1) {}
		_hashtable_imp(const _Bucket_alloc_type& _A) : _Bucket_alloc_type(_A), _Mytable(1), _Mysize(0), _Maxidx(1) {}
	};

	_hashtable_imp _Myimp;
	_ExtractKey	   _Myextract;

	const float _MAX_LOAD = 0.80f;

	float _load() const {
		return static_cast<float>(_Myimp._Mysize) / _Myimp._Maxidx;
	}

	void _rehash() {
		_Mytable_type new_table(_Myimp._Maxidx);

		for (auto& bucket : _Myimp._Mytable) {
			for (auto& val : bucket) {
				size_t hashed_key = iris::XXH64(_Myextract(val)) & (_Myimp._Maxidx - 1);
				new_table[hashed_key].push_back(val);
			}
		}

		_Myimp._Mytable = iris::move(new_table);
	}

	void _resize() {
		size_t _new_size = (_Myimp._Maxidx << 1);

		_Myimp._Mytable.resize(_new_size);
		_Myimp._Maxidx = _new_size;
		_rehash();
	}

public:
	using allocator_type = _Al;

	hashtable() : _Myimp() {}
	hashtable(const allocator_type& _A) : _Myimp(_A) {}

public:
	void bucket_insert(const value_type& _Myvalue) {
		if (_load() > _MAX_LOAD) _resize();

		const size_t hashed_key = iris::XXH64(_Myextract(_Myvalue)) & (_Myimp._Maxidx - 1);

		_Mybucket_type& bucket = _Myimp._Mytable[hashed_key];

		for (auto& val : bucket) {
			if (_Myextract(val) == _Myextract(_Myvalue)) {
				__value_update<value_type>::_S_do_it(val, _Myvalue);
				return;
			}
		}

		bucket.push_back(_Myvalue);
		++_Myimp._Mysize;
	}
};
_IRIS_END_
#endif // !_IRIS_HASHTABLE_
