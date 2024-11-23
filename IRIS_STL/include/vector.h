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
		pointer _Current = _Myimp._Mylast;
		for (; _Current != _Myimp._Myfirst; --_Current) {
			_Myimp.destroy(IRIS::__addressof(*_Current));
		}
	}

public:
	size_t capacity() const {
		return _Myimp._Myend - _Myimp._Myfirst;
	}

	size_t size() const {
		return _Myimp._Mylast - _Myimp._Myfirst;
	}

public:
	void push_back(const value_type& _Val) {
		if (_Myimp._Mylast == _Myimp._Myend);

		_Myimp.construct(_Myimp._Mylast, _Val);
		++_Myimp._Mylast;
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
			for (; _Current != _Myimp._Myfirst; --_Current) {
				_Myimp.destroy(IRIS::__addressof(*_Current));
			}
			throw bad_construct();
		}
	}
};
_IRIS_END_
#endif // _IRIS_VECTOR_
