// unordered_map.h -*- C++ -*-
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

#ifndef _IRIS_UNORDERED_MAP_
#define _IRIS_UNORDERED_MAP_

#include <cxx_config.h>
#include <hashtable.h>
#include <pair.h>

_IRIS_BEGIN_
template <typename _Key, typename _Val, typename _Al = iris::allocator<iris::pair<const _Key,_Val>>>
class unordered_map : protected hashtable<_Key, iris::pair<const _Key, _Val>, _Al, iris::map_key_extract> {
	typedef typename _Al::value_type _Myal_value_type;

	typedef hashtable<_Key, iris::pair<const _Key, _Val>, _Al, iris::map_key_extract> _Mytable;
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
	using pair_type		  = iris::pair<const _Key, _Val>;
	using allocator_type  = _Al;

protected:
	using _Mytable::_Myimp;
	using _Mytable::bucket_insert;
	using _Mytable::find_value;

public:
	unordered_map() : _Mytable() {}

public:
	void insert(const pair_type& _Mypair) {
		_Mytable::bucket_insert(_Mypair);
	}

	value_type& operator[](const _Key& _Mykey) {
		pair_type* _Tmp = _Mytable::find_value(_Mykey);
		if (_Tmp) return _Tmp->second;
		pair_type _Pair{ _Mykey, value_type() };
		return _Mytable::bucket_insert(_Pair).second;
	}
};
_IRIS_END_
#endif // _IRIS_UNORDERED_MAP_