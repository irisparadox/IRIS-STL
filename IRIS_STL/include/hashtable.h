// hashtable.h -*- C++ -*-
//
// Copyright (C) 2024 irisparadox
//
// This file is part of the IRIS::STL C++ Library, licensed under the MIT License.
// You may obtain a copy of the License at:
//
//     https://opensource.org/licenses/MIT
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal in
// the Software without restriction, including without limitation the rights to use,
// copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the
// Software, and to permit persons to whom the Software is furnished to do so, subject
// to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
// FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
// COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
// AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
// WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

/** @file hashtable.h
 *  @brief Internal header file for the hashtable implementation in IRIS::STL.
 *
 *  This is an internal file used by other parts of the library. It should not be included
 *  or used directly in your code. Instead, use @headername{unordered_map, unordered_set}.
 *
 *  ### Hashtable Concept
 *  A hash table organizes values into "buckets" using a hash function. Each bucket
 *  stores values or key-value pairs, typically using a linked list to handle collisions.
 *  The hash function computes an index to place the values in the appropriate bucket.
 *
 *  #### Example:
 *  Using "meow", "purr", "woof", and "bark" as keys, a hash table might distribute them
 *  across buckets like so:
 *
 *  ```
 *  +---+      +---+
 *  | 0 | ---> | V | ["meow"]
 *  +---+      +---+
 *  +---+      +---+      +---+
 *  | 1 | ---> | V | ---> | V | ["woof", "bark"]
 *  +---+      +---+      +---+
 *  +---+
 *  | 2 |
 *  +---+
 *  +---+      +---+
 *  | 3 | ---> | V | ["purr"]
 *  +---+      +---+
 *  ```
 *
 *  ### Explanation:
 *  - "meow" hashes to bucket 0, so it is placed in the corresponding list.
 *  - "woof" hashes to bucket 1, but "bark" also hashes to bucket 1, causing a collision.
 *    Both are stored in the linked list for that bucket.
 *  - "purr" hashes to bucket 3 and is placed there.
 *
 *  Hash tables often use linked lists for simplicity, but this comes at the cost of
 *  more cache misses. Alternative designs (e.g., open addressing) reduce cache misses
 *  but are more complex to implement. In this library, linked lists provide a balance
 *  between simplicity and functionality.
 */


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

	const size_t _hash_calc(const _Key& _Mykey) const {
		return iris::XXH64(_Mykey) & (_Myimp._Maxidx - 1);
	}

	void _rehash() {
		_Mytable_type new_table(_Myimp._Maxidx);

		for (auto& bucket : _Myimp._Mytable) {
			for (auto& val : bucket) {
				size_t hashed_key = _hash_calc(_Myextract(val));
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
	value_type& bucket_insert(const value_type& _Myvalue) {
		if (_load() > _MAX_LOAD) _resize();

		const size_t hashed_key = _hash_calc(_Myextract(_Myvalue));

		_Mybucket_type& bucket = _Myimp._Mytable[hashed_key];

		for (auto& val : bucket) {
			if (_Myextract(val) == _Myextract(_Myvalue)) {
				__value_update<value_type>::_S_do_it(val, _Myvalue);
				return val;
			}
		}

		bucket.push_back(_Myvalue);
		++_Myimp._Mysize;
		return bucket.back();
	}

	value_type* find_value(const _Key& _Mykey) {
		const size_t hashed_key = _hash_calc(_Mykey);

		_Mybucket_type& bucket = _Myimp._Mytable[hashed_key];

		for (auto& val : bucket) {
			if (_Myextract(val) == _Mykey) {
				return &val;
			}
		}

		return nullptr;
	}
};
_IRIS_END_
#endif // !_IRIS_HASHTABLE_
