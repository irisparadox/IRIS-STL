#ifndef _IRIS_KEY_EXTRACTOR_
#define _IRIS_KEY_EXTRACTOR_

#include <cxx_config.h>
#include <pair.h>

_IRIS_BEGIN_
struct map_key_extract {
	template <typename _Ty1, typename _Ty2>
	auto operator()(const pair<_Ty1, _Ty2>& _Mypair) const -> const _Ty1& {
		return _Mypair.first;
	}
};

struct set_key_extract {
	template <typename _Ty>
	auto operator()(const _Ty& _Myval) const -> const _Ty& {
		return _Myval;
	}
};
_IRIS_END_
#endif // _IRIS_KEY_EXTRACTOR_
