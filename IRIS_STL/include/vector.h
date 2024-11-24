#ifndef _IRIS_VECTOR_
#define _IRIS_VECTOR_

#include <cxx_config.h>
#include <allocator.h>

_IRIS_BEGIN_
class bad_construct : public exception {
public:
	bad_construct() throw() {}
	~bad_construct() throw() {}

	const char* what() const throw() { return "bad object construct"; }
};

class length_error : public exception {
public:
	length_error() throw() {}
	~length_error() throw() {}
	
	const char* what() const throw() { return "specified length is over the limit"; }
};

template<typename _Ty, typename _Al>
struct _Vector_base {
	typedef typename _Al::template rebind<_Ty>::other _Myal_type;

	struct _Vector_imp : public _Myal_type {
		typename _Myal_type::pointer _Myfirst;
		typename _Myal_type::pointer _Mylast;
		typename _Myal_type::pointer _Myend;

		_Vector_imp() : _Myal_type(), _Myfirst(0), _Mylast(0), _Myend(0) {}
		_Vector_imp(_Myal_type const& _A) : _Myal_type(_A), _Myfirst(0), _Mylast(0), _Myend(0) {}
	};

public:
	typedef _Al allocator_type;

	_Vector_base() : _Myimp() {}
	_Vector_base(const allocator_type& _Alloc) : _Myimp(_Alloc) {}
	_Vector_base(size_t _Size) : _Myimp() {
		_Myimp._Myfirst = _Alloc(_Size);
		_Myimp._Mylast  = _Myimp._Myfirst;
		_Myimp._Myend	= _Myimp._Myfirst + _Size;
	}
	_Vector_base(size_t _Size, const allocator_type& _Alloc) : _Myimp(_Alloc) {
		_Myimp._Myfirst = _Alloc(_Size);
		_Myimp._Mylast = _Myimp._Myfirst;
		_Myimp._Myend = _Myimp._Myfirst + _Size;
	}

	~_Vector_base() {
		_Dealloc(_Myimp._Myfirst, _Myimp._Myend - _Myimp._Myfirst);
	}

public:
	_Myal_type& _Getal_type() {
		return *static_cast<_Myal_type*>(&_Myimp);
	}

	const _Myal_type& _Getal_type() const {
		return *static_cast<const _Myal_type*>(&_Myimp);
	}

	allocator_type _Getal() const {
		return allocator_type(_Getal_type());
	}

public:
	_Vector_imp _Myimp;

	typename _Myal_type::pointer _Alloc(size_t _Size) {
		return _Size != 0 ? _Myimp.allocate(_Size) : 0;
	}

	void _Dealloc(typename _Myal_type::pointer _Ptr, size_t _Size) {
		if (_Ptr) _Myimp.deallocate(_Ptr, _Size);
	}
};

template <typename _Ty, typename _Al = IRIS::allocator<_Ty>>
class vector : protected _Vector_base<_Ty, _Al> {
	typedef typename _Al::value_type _Myal_value_type;

	typedef _Vector_base<_Ty, _Al>		 _Mybase;
	typedef typename _Mybase::_Myal_type _Myal_type;

public:
	using value_type	  = _Ty;
	using size_type		  = size_t;
	using difference_type = ptrdiff_t;
	using pointer		  = _Ty*;
	using const_pointer   = const _Ty*;
	using reference		  = _Ty&;
	using const_reference = const _Ty&;
	using allocator_type  = _Al;

protected:
	using _Mybase::_Alloc;
	using _Mybase::_Dealloc;
	using _Mybase::_Myimp;
	using _Mybase::_Getal_type;
	using _Mybase::_Getal;

public:

	/**
	*   @brief Default constructor of vector with no elements.
	*/
	vector() : _Mybase() {}

	/**
	*   @brief Constructor of vector with no elements, given an allocator.
	*	@param _Alloc An allocator object.
	*/
	explicit vector(const allocator_type& _Alloc) : _Mybase(_Alloc) {}

	/**
	*   @brief Constructor of vector with no elements, given an initial size.
	*	@param _Size Vector initial size.
	*/
	explicit vector(size_type _Size) : _Mybase(_Size) {
		_Default_initialization(_Size);
	}

	~vector() {
		_Destroy();
	}

public:
	reference front() {
		return *_Myimp._Myfirst;
	}

	const_reference front() const {
		return *_Myimp._Myfirst;
	}

	reference back() {
		return *(_Myimp._Mylast - 1);
	}

	const_reference back() const {
		return *(_Myimp._Mylast - 1);
	}

public:
	bool empty() const {
		return _Myimp._Myfirst == _Myimp._Mylast;
	}

	size_t size() const {
		return _Myimp._Mylast - _Myimp._Myfirst;
	}
	
	size_t max_size() const {
		return _Myimp.max_size();
	}

	void reserve(size_t _Size) {
		if (_Size > max_size()) _Elength_();
		if (_Size < capacity()) return;

		const size_type _old_size = size();
		pointer _tmp = _Allocate_and_copy(_Size, _Myimp._Myfirst, _Myimp._Mylast);
		_Destroy();
		_Dealloc(_Myimp._Myfirst, _Myimp._Myend - _Myimp._Myfirst);
		_Myimp._Myfirst = _tmp;
		_Myimp._Mylast  = _tmp + _old_size;
		_Myimp._Myend	= _Myimp._Myfirst + _Size;
	}

	size_t capacity() const {
		return _Myimp._Myend - _Myimp._Myfirst;
	}

public:
	void push_back(const value_type& _Val) {
		if (_Myimp._Mylast == _Myimp._Myend) reserve(_New_capacity());

		_Myimp.construct(_Myimp._Mylast, _Val);
		++_Myimp._Mylast;
	}

private:
	size_t _New_capacity() {
		size_t _old = capacity();
		return (_old > 1) ? _old + (_old / 2) : ++_old;
	}
	
private:
	void _Default_initialization(size_t _Size) {
		pointer _Current = _Myimp._Myfirst;
		try {
			for (; _Size > 0; --_Size, ++_Current) {
				_Myimp.construct(IRIS::__addressof(*_Current));
			}
		}
		catch (...) {
			for (; _Current >= _Myimp._Myfirst; --_Current) {
				_Myimp.destroy(IRIS::__addressof(*_Current));
			}
			_Econstruct_();
		}
	}

	pointer _Allocate_and_copy(size_t _Size, pointer _First, pointer _Last) {
		pointer _result = _Myimp.allocate(_Size);
		pointer _Current = _result;
		try {
			for (; _First != _Last; ++_First, ++_Current) {
				_Myimp.construct(IRIS::__addressof(*_Current), *_First);
			}
			return _result;
		}
		catch (...) {
			for (; _Current >= _result; --_Current) {
				_Myimp.destroy(IRIS::__addressof(*_Current));
				_Econstruct_();
			}
		}
	}

	void _Destroy() {
		pointer _Current = _Myimp._Myfirst;
		for (; _Current != _Myimp._Mylast; ++_Current) {
			_Myimp.destroy(IRIS::__addressof(*_Current));
		}
	}

private:
	[[noreturn]] void _Elength_() {
		throw length_error();
	}

	[[noreturn]] void _Econstruct_() {
		throw bad_construct();
	}
};
_IRIS_END_
#endif // _IRIS_VECTOR_
