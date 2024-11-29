#ifndef _IRIS_HASHTABLE_TRAITS_
#define _IRIS_HASHTABLE_TRAITS_

#include <cxx_config.h>
#include <pair.h>

_IRIS_BEGIN_
template <typename _Val>
struct __value_update {
	static void _S_do_it(_Val& _stored, const _Val& _new) {
		_stored = _new;
	}
};

template <typename _Key, typename _Val>
struct __value_update<pair<const _Key, _Val>> {
	static void _S_do_it(pair<const _Key, _Val>& _stored, const pair<const _Key, _Val>& _new) {
		_stored.second = _new.second;
	}
};
_IRIS_END_
#endif // _IRIS_HASHTABLE_TRAITS_
