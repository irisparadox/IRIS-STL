#ifndef _IRIS_VECTOR_
#define _IRIS_VECTOR_

#include <cxx_config.h>
#include <initializer_list>
#include <allocator.h>

_IRIS_BEGIN_
class bad_construct : public exception {
public:
	bad_construct() throw() {}
	~bad_construct() throw() {}

	const char* what() const throw() { return "bad object construct in iris::vector"; }
};

class length_error : public exception {
public:
	length_error() throw() {}
	~length_error() throw() {}
	
	const char* what() const throw() { return "specified length is over the limit in iris::vector"; }
};

class out_of_range : public exception {
public:
	out_of_range() throw() {}
	~out_of_range() throw() {}

	const char* what() const throw() { return "specified index is out of range in iris::vector"; }
};

template <typename _Ty>
class _Vector_const_iterator {
public:
	using value_type	  = _Ty;
	using const_pointer	  = const _Ty*;
	using const_reference = const _Ty&;
	using size_type		  = size_t;
	using difference_type = ptrdiff_t;

	_Vector_const_iterator() throw() : _Ptr(), _Idx() {}
	explicit _Vector_const_iterator(const_pointer _Pvec, difference_type _Off = 0) throw() : _Ptr(_Pvec), _Idx(_Off) {}

public:
	_ILIBCXX_CONSTEXPR const_reference operator*() const throw() {
		return *operator->();
	}

	_ILIBCXX_CONSTEXPR const_pointer operator->() const throw() {
		return _Ptr + _Idx;
	}

	_ILIBCXX_CONSTEXPR _Vector_const_iterator& operator++() throw() {
		++_Idx;
		return *this;
	}

	_ILIBCXX_CONSTEXPR _Vector_const_iterator operator++(int) throw() {
		_Vector_const_iterator _Tmp = *this;
		++*this;
		return _Tmp;
	}

	_ILIBCXX_CONSTEXPR _Vector_const_iterator& operator--() throw() {
		--_Idx;
		return *this;
	}

	_ILIBCXX_CONSTEXPR _Vector_const_iterator operator--(int) throw() {
		_Vector_const_iterator _Tmp = *this;
		--*this;
		return _Tmp;
	}

	_ILIBCXX_CONSTEXPR bool operator==(const _Vector_const_iterator& _Right) const throw() {
		return _Idx == _Right._Idx;
	}

	_ILIBCXX_CONSTEXPR bool operator!=(const _Vector_const_iterator& _Right) const throw() {
		return _Idx != _Right._Idx;
	}

	_ILIBCXX_CONSTEXPR bool operator<(const _Vector_const_iterator& _Right) const throw() {
		return _Idx < _Right._Idx;
	}

	_ILIBCXX_CONSTEXPR bool operator>(const _Vector_const_iterator& _Right) const throw() {
		return _Idx > _Right._Idx;
	}

	_ILIBCXX_CONSTEXPR bool operator<=(const _Vector_const_iterator& _Right) const throw() {
		return _Idx <= _Right._Idx;
	}

	_ILIBCXX_CONSTEXPR bool operator>=(const _Vector_const_iterator& _Right) const throw() {
		return _Idx >= _Right._Idx;
	}

	_ILIBCXX_CONSTEXPR const_reference operator[](const difference_type _Off) const throw() {
		return *(*this + _Off);
	}

protected:
	const_pointer _Ptr;
	difference_type _Idx;
};

template <typename _Ty>
class _Vector_iterator : public _Vector_const_iterator<_Ty> {
public:
	using _Mybase = _Vector_const_iterator<_Ty>;

	using pointer	      = _Ty*;
	using reference		  = _Ty&;
	using size_type		  = size_t;
	using difference_type = ptrdiff_t;

	_Vector_iterator() throw() : _Ptr(), _Idx() {}
	explicit _Vector_iterator(pointer _Pvec, difference_type _Off) throw() : _Mybase(_Pvec, _Off) {}

protected:
	using _Mybase::_Ptr;
	using _Mybase::_Idx;

public:
	_ILIBCXX_CONSTEXPR reference operator*() const throw() {
		return const_cast<reference>(_Mybase::operator*());
	}

	_ILIBCXX_CONSTEXPR pointer operator->() const throw() {
		return this->_Ptr;
	}

	_ILIBCXX_CONSTEXPR _Vector_iterator& operator++() throw() {
		_Mybase::operator++();
		return *this;
	}

	_ILIBCXX_CONSTEXPR _Vector_iterator operator++(int) throw() {
		_Vector_iterator _Tmp = *this;
		_Mybase::operator++();
		return _Tmp;
	}

	_ILIBCXX_CONSTEXPR _Vector_iterator& operator--() throw() {
		_Mybase::operator--();
		return *this;
	}

	_ILIBCXX_CONSTEXPR _Vector_iterator operator-(int) throw() {
		_Vector_iterator _Tmp = *this;
		_Mybase::operator--();
		return _Tmp;
	}

	_ILIBCXX_CONSTEXPR reference operator[](const difference_type _Off) const throw() {
		return const_cast<reference>(_Mybase::operator[](_Off));
	}
};

template <typename _Ty, typename _Al>
struct _Vector_base {
	typedef typename _Al::template rebind<_Ty>::other _Ty_al_type;

	struct _Vector_imp : public _Ty_al_type {
		typename _Ty_al_type::pointer _Myfirst;
		typename _Ty_al_type::pointer _Mylast;
		typename _Ty_al_type::pointer _Myend;

		_Vector_imp() : _Ty_al_type(), _Myfirst(0), _Mylast(0), _Myend(0) {}
		_Vector_imp(_Ty_al_type const& _A) : _Ty_al_type(_A), _Myfirst(0), _Mylast(0), _Myend(0) {}
	};

public:
	typedef _Al allocator_type;

	_Vector_base() : _Myimp() {}
	_Vector_base(const allocator_type& _A) : _Myimp(_A) {}
	_Vector_base(size_t _Size) : _Myimp() {
		_Myimp._Myfirst = _Alloc(_Size);
		_Myimp._Mylast  = _Myimp._Myfirst;
		_Myimp._Myend	= _Myimp._Myfirst + _Size;
	}
	_Vector_base(size_t _Size, const allocator_type& _A) : _Myimp(_A) {
		_Myimp._Myfirst = _Alloc(_Size);
		_Myimp._Mylast = _Myimp._Myfirst;
		_Myimp._Myend = _Myimp._Myfirst + _Size;
	}

#if __CXX_HASCXX0X__
	_Vector_base(_Vector_base&& _Right) : _Myimp(_Right._Getal_type()) {
		_Myimp._Myfirst = _Right._Myimp._Myfirst;
		_Myimp._Mylast  = _Right._Myimp._Mylast;
		_Myimp._Myend	= _Right._Myimp._Myend;

		_Right._Myimp._Myfirst = nullptr;
		_Right._Myimp._Mylast  = nullptr;
		_Right._Myimp._Myend   = nullptr;
	}
#endif // __CXX_HASCXX0X__


	~_Vector_base() {
		_Dealloc(_Myimp._Myfirst, _Myimp._Myend - _Myimp._Myfirst);
	}

public:
	_Ty_al_type& _Getal_type() {
		return *static_cast<_Ty_al_type*>(&_Myimp);
	}

	const _Ty_al_type& _Getal_type() const {
		return *static_cast<const _Ty_al_type*>(&_Myimp);
	}

	allocator_type _Getal() const {
		return allocator_type(_Getal_type());
	}

public:
	_Vector_imp _Myimp;

	typename _Ty_al_type::pointer _Alloc(size_t _Size) {
		return _Size != 0 ? _Myimp.allocate(_Size) : 0;
	}

	void _Dealloc(typename _Ty_al_type::pointer _Ptr, size_t _Size) {
		if (_Ptr) _Myimp.deallocate(_Ptr, _Size);
	}
};

template <typename _Ty, typename _Al = iris::allocator<_Ty>>
class vector : protected _Vector_base<_Ty, _Al> {
	typedef typename _Al::value_type _Myal_value_type;

	typedef _Vector_base<_Ty, _Al>		  _Mybase;
	typedef typename _Mybase::_Ty_al_type _Ty_al_type;

public:
	using value_type	  = _Ty;
	using size_type		  = size_t;
	using difference_type = ptrdiff_t;
	using pointer		  = _Ty*;
	using const_pointer   = const _Ty*;
	using reference		  = _Ty&;
	using const_reference = const _Ty&;
	using allocator_type  = _Al;

	using const_iterator = _Vector_const_iterator<_Ty>;
	using iterator		 = _Vector_iterator<_Ty>;

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
	*	@param A An allocator object.
	*/
	explicit vector(const allocator_type& _A) : _Mybase(_A) {}

#if __CXX_HASCXX0X__
	/**
	*   @brief Constructor of vector with no elements, given an initial size.
	*	@param N Vector initial size.
	*/
	explicit vector(size_type _N) : _Mybase(_N) {
		_Default_initialization(_N);
	}

	/**
	*	@brief Constructor of vector with a default value.
	*	@param N   Vector initial size.
	*	@param val The default value.
	*	@param A   An allocator object.
	*/
	explicit vector(size_type _N, const value_type& _Val, const allocator_type& _A = allocator_type())
		: _Mybase(_N, _A)
	{ _Fill_initialization(_N, _Val); }
#else
	/**
	*	@brief Constructor of vector with a default value.
	*	@param N   Vector initial size.
	*	@param val The default value.
	*	@param A   An allocator object.
	*/
	explicit vector(size_type _N, const value_type& _Val = value_type(), const allocator_type& _A = allocator_type())
		: _Mybase(_N, _A)
	{ _Fill_initialization(_N, _Val); }
#endif // _CXX_HASCXX0X__

	/**
	*	@brief Copy constructor of vector.
	*	@param Right A vector matching element and allocator types.
	*/
	vector(const vector& _Right) : _Mybase(_Right.size(), _Right._Getal_type()) {
		_Myimp._Mylast = _uninitialized_copy(_Right._Myimp._Myfirst, _Right._Myimp._Mylast, _Myimp._Myfirst);
	}


	/**
	*	@brief Move constructor of vector.
	*	@param Right A vector matching element and allocator types.
	*/
	vector(vector&& _Right) throw() : _Mybase(iris::move(_Right)) {}


	/**
	*	@brief Creates a vector given an initializer list.
	*	@param L An initializer list matching element type.
	*	@param A An allocator object.
	*/
	vector(std::initializer_list<value_type> _L, const allocator_type& _A) : _Mybase(_A) {
		assign(_L);
	}

	void assign(std::initializer_list<value_type>& _L) {
		for (auto val : _L) {
			push_back(val);
		}
	}

	~vector() {
		_Destroy();
	}

public:
	iterator begin() throw() {
		return iterator(_Myimp._Myfirst, 0);
	}

	iterator end() throw() {
		return iterator(_Myimp._Mylast, size());
	}

	const_iterator cbegin() throw() {
		return const_iterator(_Myimp._Myfirst, 0);
	}

	const_iterator cend() throw() {
		return const_iterator(_Myimp._Mylast, size());
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

	reference at(size_type _Idx) {
		_Range_check(_Idx);
		return (*this)[_Idx];
	}

	const_reference at(size_type _Idx) const {
		_Range_check(_Idx);
		return (*this)[_Idx];
	}

public:
	reference operator[](size_type _Idx) {
		return *(_Myimp._Myfirst + _Idx);
	}

	const_reference operator[](size_type _Idx) const {
		return *(_Myimp._Myfirst + _Idx);
	}

public:
	bool empty() const {
		return _Myimp._Myfirst == _Myimp._Mylast;
	}

	size_type size() const {
		return _Myimp._Mylast - _Myimp._Myfirst;
	}
	
	size_type max_size() const {
		return _Myimp.max_size();
	}

	void reserve(size_type _Size) {
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

	size_type capacity() const {
		return _Myimp._Myend - _Myimp._Myfirst;
	}

public:
	void push_back(const value_type& _Val) {
		if (_Myimp._Mylast == _Myimp._Myend) reserve(_New_capacity());

		_Myimp.construct(_Myimp._Mylast, _Val);
		++_Myimp._Mylast;
	}

#if __CXX_HASCXX0X__
	void push_back(value_type&& _Val) {
		if (_Myimp._Mylast == _Myimp._Myend) reserve(_New_capacity());

		_Myimp.construct(_Myimp._Mylast, iris::move(_Val));
		++_Myimp._Mylast;
	}
#endif // __CXX_HASCXX0X__

	void pop_back() {
		--_Myimp._Mylast;
		_Myimp.destroy(_Myimp._Mylast);
	}

private:
	size_type _New_capacity() {
		size_type _old = capacity();
		return (_old > 1) ? _old + (_old / 2) : ++_old;
	}

	void _Range_check(size_type _Idx) const {
		if (_Idx >= size()) throw out_of_range();
	}
	
private:
	void _Fill_initialization(size_type _Size, const value_type& _Val) {
		_Default_fill_initialization(_Size,_Val);
		_Myimp._Mylast = _Myimp._Myend;
	}

	void _Default_fill_initialization(size_type _Size, const value_type& _Val) {
		pointer _Current = _Myimp._Myfirst;
		try {
			for (; _Size > 0; --_Size, ++_Current) {
				_Myimp.construct(iris::__addressof(*_Current), _Val);
			}
		}
		catch (...) {
			for (; _Current >= _Myimp._Myfirst; --_Current) {
				_Myimp.destroy(iris::__addressof(*_Current));
			}
			_Econstruct_();
		}
	}

	void _Default_initialization(size_type _Size) {
		pointer _Current = _Myimp._Myfirst;
		try {
			for (; _Size > 0; --_Size, ++_Current) {
				_Myimp.construct(iris::__addressof(*_Current));
			}
		}
		catch (...) {
			for (; _Current >= _Myimp._Myfirst; --_Current) {
				_Myimp.destroy(iris::__addressof(*_Current));
			}
			_Econstruct_();
		}
	}

	pointer _Allocate_and_copy(size_type _Size, pointer _First, pointer _Last) {
		pointer _result = _Myimp.allocate(_Size);
		_uninitialized_copy(_First, _Last, _result);
		return _result;
	}

	pointer _uninitialized_copy(pointer _First, pointer _Last, pointer _result) {
		pointer _Current = _result;
		try {
			for (; _First != _Last; ++_First, ++_Current) {
				_Myimp.construct(iris::__addressof(*_Current), *_First);
			}
			return _Current;
		}
		catch (...) {
			for (; _Current >= _result; --_Current) {
				_Myimp.destroy(iris::__addressof(*_Current));
				_Econstruct_();
			}
		}
	}

	void _Destroy() {
		pointer _Current = _Myimp._Myfirst;
		for (; _Current != _Myimp._Mylast; ++_Current) {
			_Myimp.destroy(iris::__addressof(*_Current));
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