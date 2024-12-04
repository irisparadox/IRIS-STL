#ifndef _IRIS_LIST_
#define _IRIS_LIST_

#include <cxx_config.h>
#include <initializer_list>
#include <allocator.h>

_IRIS_BEGIN_
template <typename _Ty>
struct _Node {
	using _Nodeptr = _Node*;
	using _Noderef = _Node&;

	_Nodeptr _Next;
	_Nodeptr _Prev;
	_Ty _Myval;

#if __CXX_HASCXX0X__
	template <typename... _Args>
	_Node(_Args&&... _Myargs) : _Myval(iris::forward<_Args>(_Myargs)...) {}
#endif // __CXX_HASCXX0X__

	static void swap(_Noderef _Left, _Noderef _Right) throw() {
		using iris::swap;
		swap(_Left, _Right);
	}

	void _transfer(_Nodeptr const _First, _Nodeptr const _Last) throw() {
		if (this != _Last) {
			_Last->_Prev->_Next  = this;
			_First->_Prev->_Next = _Last;
			this->_Prev->_Next	 = _First;

			_Nodeptr const _Tmp = this->_Prev;
			this->_Prev			= _Last->_Prev;
			_Last->_Prev		= _First->_Prev;
			_First->_Prev		= _Tmp;
		}
	}

	void _reverse() throw() {
		using iris::swap;
		_Nodeptr _Tmp = this;
		do {
			swap(_Tmp->_Next, _Tmp->_Prev);

			_Tmp = _Tmp->_Prev;
		} while (_Tmp != this);
	}

	void _hook(_Nodeptr const _Pos) throw() {
		this->_Next = _Pos;
		this->_Prev = _Pos->_Prev;
		_Pos->_Prev->_Next = this;
		_Pos->_Prev		   = this;
	}

	void _unhook() throw() {
		_Nodeptr const _Next_node = this->_Next;
		_Nodeptr const _Prev_node = this->_Prev;
		_Prev_node->_Next = _Next_node;
		_Next_node->_Prev = _Prev_node;
	}

	template <class _Alnode>
	static _Nodeptr _Buyhead(_Alnode& _Al) throw() {
		const auto _Result = _Al.allocate(1);
		_Al.construct_in_place(_Result->_Prev, _Result);
		_Al.construct_in_place(_Result->_Next, _Result);
		return _Result;
	}

	template <class _Alnode>
	static void _Freenode0(_Alnode& _Al, _Nodeptr _Ptr) throw() {
		_Al.destroy_in_place(_Ptr->_Next);
		_Al.destroy_in_place(_Ptr->_Prev);
		_Al.deallocate(_Ptr, 1);
	}

	template <class _Alnode>
	static void _Freenode(_Alnode& _Al, _Nodeptr _Ptr) throw() {
		_Al.destroy_in_place(_Ptr->_Myval);
		_Freenode0(_Al, _Ptr);
	}

	template <class _Alnode>
	static void _Freenonhead(_Alnode& _Al, _Nodeptr _Head) throw() {
		_Head->_Prev->_Next = nullptr;
		auto _Pnode = _Head->_Next;
		for (_Nodeptr _Pnext; _Pnode; _Pnode = _Pnext) {
			_Pnext = _Pnode->_Next;
			_Freenode(_Al, _Pnode);
		}
	}
};

template <typename _Ty>
class _List_const_iterator {
public:
	using _Node			  = _Node<_Ty>;
	using const_pointer	  = const _Ty*;
	using const_reference = const _Ty&;
	using size_type		  = size_t;
	using difference_type = ptrdiff_t;

	typedef _List_const_iterator _Self;
	
	_List_const_iterator() throw() : _Ptr(), _Idx() {}
	explicit _List_const_iterator(_Node* _Pnode) throw() : _Ptr(_Pnode), _Idx(0) {}

public:
	_ILIBCXX_CONSTEXPR const_reference operator*() const throw() {
		return *operator->();
	}

	_ILIBCXX_CONSTEXPR const_pointer operator->() const throw() {
		return iris::__addressof(_Ptr->_Myval);
	}

	_ILIBCXX_CONSTEXPR _Self& operator++() throw() {
		_Ptr = _Ptr->_Next;
		++_Idx;
		return *this;
	}

	_ILIBCXX_CONSTEXPR _Self operator++(int) throw() {
		_Self _Tmp = *this;
		++*this;
		return _Tmp;
	}

	_ILIBCXX_CONSTEXPR _Self& operator--() throw() {
		_Ptr = _Ptr->_Prev;
		--_Idx;
		return *this;
	}

	_ILIBCXX_CONSTEXPR _Self operator--(int) throw() {
		_Self _Tmp = *this;
		--*this;
		return _Tmp;
	}

	_ILIBCXX_CONSTEXPR bool operator==(const _Self& _Right) const throw() {
		return _Ptr == _Right._Ptr;
	}

	_ILIBCXX_CONSTEXPR bool operator!=(const _Self& _Right) const throw() {
		return !(*this == _Right);
	}

public:
	_Node* _Ptr;
	difference_type _Idx;
};

template <typename _Ty>
class _List_iterator : public _List_const_iterator<_Ty> {
public:
	using _Mybase = _List_const_iterator<_Ty>;

	using _Self			  = _List_iterator;
	using _Node			  = _Node<_Ty>;
	using pointer		  = _Ty*;
	using reference		  = _Ty&;
	using size_type		  = size_t;
	using difference_type = ptrdiff_t;

	_List_iterator() throw() : _Mybase() {}
	explicit _List_iterator(_Node* _Pnode) : _Mybase(_Pnode) {}

public:
	using _Mybase::_Ptr;
	using _Mybase::_Idx;

public:
	_ILIBCXX_CONSTEXPR reference operator*() const throw() {
		return const_cast<reference>(_Mybase::operator*());
	}

	_ILIBCXX_CONSTEXPR pointer operator->() const throw() {
		return iris::__addressof(_Ptr->_Myval);
	}

	_ILIBCXX_CONSTEXPR _Self& operator++() throw() {
		_Mybase::operator++();
		return *this;
	}

	_ILIBCXX_CONSTEXPR _Self operator++(int) throw() {
		_Self _Tmp = *this;
		_Mybase::operator++();
		return _Tmp;
	}

	_ILIBCXX_CONSTEXPR _Self& operator--() throw() {
		_Mybase::operator--();
		return *this;
	}

	_ILIBCXX_CONSTEXPR _Self operator--(int) throw() {
		_Self _Tmp = *this;
		_Mybase::operator--();
		return _Tmp;
	}
};

template <typename _Ty, typename _Al>
class _List_base {
protected:
	typedef typename _Al::template rebind<_Node<_Ty>>::other _Node_alloc_type;
	typedef typename _Al::template rebind<_Ty>::other _Ty_alloc_type;

	typedef typename _Node<_Ty>::_Nodeptr _Nodeptr;
	using _Node = _Node<_Ty>;

	struct _List_imp : public _Node_alloc_type {
		_Nodeptr _Myhead;
		size_t   _Mysize;

		_List_imp() : _Node_alloc_type(), _Myhead(), _Mysize(0) {}
		_List_imp(const _Node_alloc_type& _A) : _Node_alloc_type(_A), _Myhead(), _Mysize(0) {}
	};

	_List_imp _Myimp;

	_Nodeptr get_node() {
		return _Myimp._Node_alloc_type::allocate(1);
	}

	void del_node(_Nodeptr _Pnode) {
		_Myimp._Node_alloc_type::deallocate(_Pnode, 1);
	}

public:
	typedef _Al allocator_type;

	_Node_alloc_type& _Getnodal() {
		return *static_cast<_Node_alloc_type*>(&this->_Myimp);
	}

	const _Node_alloc_type& _Getnodal() const {
		return *static_cast<const _Node_alloc_type*>(&this->_Myimp);
	}

	_Ty_alloc_type _Getyal() const {
		return _Ty_alloc_type(_Getnodal());
	}

	allocator_type _Getal() const {
		return allocator_type(_Getnodal());
	}

	_List_base() : _Myimp() {
		_init();
	}

	_List_base(const allocator_type& _A) : _Myimp(_A) {
		_init();
	}

#if __CXX_HASCXX0X__
	_List_base(_List_base&& _Mylistbase) : _Myimp(_Mylistbase._Getnodal()) {
		_init();
		_Node::swap(this->_Myimp._Myhead, _Mylistbase._Myimp._Myhead);
	}
#endif // __CXX_HASCXX0X__

	~_List_base() {
		_Node::_Freenonhead(_Getnodal(), _Myimp._Myhead);
		_Node::_Freenode0(_Getnodal(), _Myimp._Myhead);
		_Myimp._Myhead = nullptr;
		_Myimp._Mysize = 0;
	}

	void _init() {
		_Myimp._Myhead = _Node::_Buyhead(_Getnodal());
	}
};

template <typename _Ty, typename _Al = iris::allocator<_Ty>>
class list : protected _List_base<_Ty, _Al> {
	typedef typename _Al::value_type _Myal_value_type;

	typedef _List_base<_Ty, _Al>			 _Mybase;
	typedef typename _Mybase::_Ty_alloc_type _Ty_alloc_type;

public:
	using value_type	  = _Ty;
	using size_type		  = size_t;
	using difference_type = ptrdiff_t;
	using pointer		  = _Ty*;
	using const_pointer	  = const _Ty*;
	using reference		  = _Ty&;
	using const_reference = const _Ty&;
	using allocator_type  = _Al;

	using const_iterator = _List_const_iterator<_Ty>;
	using iterator		 = _List_iterator<_Ty>;

protected:
	using _Mybase::_Myimp;
	using _Mybase::get_node;
	using _Mybase::del_node;
	using _Mybase::_Getnodal;
	using _Mybase::_Getyal;
	using _Node	= _Node<_Ty>;
	typedef typename _Node::_Nodeptr _Nodeptr;

public:

	/**
	*	@brief Creates an empty list.
	*/
	list() : _Mybase() {}

	/**
	*	@brief Creates an empty list.
	*	@param A An allocator object.
	*/
	explicit list(const allocator_type& _A) : _Mybase(_A) {}

	/**
	*	@brief The copy constructor of list.
	*	@param Right A list matching both element and allocator types.
	*/
	list(const list& _Right) : _Mybase(_Right._Getnodal()) {
		_initialize_dispatch(_Right._Myimp._Myhead->_Next, _Right._Myimp._Myhead);
	}

	/**
	*	@brief Creates a list given an initializer list.
	*	@param L An initializer list matching element type.
	*	@param A An allocator object.
	*/
	list(std::initializer_list<value_type> _L, const allocator_type& _A = allocator_type()) : _Mybase(_A) {
		assign(_L);
	}

	list& operator=(std::initializer_list<value_type> _L) {
		assign(_L);
	}

	void assign(std::initializer_list<value_type>& _L) {
		for (auto val : _L) {
			push_back(val);
		}
	}

	~list() {}

public:
	iterator begin() {
		return iterator(_Myimp._Myhead->_Next);
	}

	iterator end() {
		return iterator(_Myimp._Myhead);
	}

	const_iterator cbegin() const {
		return const_iterator(_Myimp._Myhead->_Next);
	}

	const_iterator cend() const {
		return const_iterator(_Myimp._Myhead);
	}

public:
	reference front() {
		return _Myimp._Myhead->_Next->_Myval;
	}

	const_reference front() const {
		return _Myimp._Myhead->_Next->_Myval;
	}

	reference back() {
		return _Myimp._Myhead->_Prev->_Myval;
	}

	const_reference back() const {
		return _Myimp._Myhead->_Prev->_Myval;
	}

public:
	_ILIBCXX_CONSTEXPR bool empty() const {
		return _Myimp._Mysize == 0;
	}

	_ILIBCXX_CONSTEXPR size_type size() const {
		return _Myimp._Mysize;
	}

	_ILIBCXX_CONSTEXPR size_type max_size() const {
		return _Myimp.max_size();
	}

public:
	void push_front(const value_type& _Val) {
		_Nodeptr _Tmp = _create_node(_Val);
		_Tmp->_hook(_Myimp._Myhead->_Next);
		++_Myimp._Mysize;
	}

#if __CXX_HASCXX0X__
	void push_front(value_type&& _Val) {
		_Nodeptr _Tmp = _create_node(iris::move(_Val));
		_Tmp->_hook(_Myimp._Myhead->_Next);
		++_Myimp._Mysize;
	}
#endif // __CXX_HASCXX0X__

	void push_back(const value_type& _Val) {
		_Nodeptr _Tmp = _create_node(_Val);
		_Tmp->_hook(_Myimp._Myhead);
		++_Myimp._Mysize;
	}
#if __CXX_HASCXX0X__
	void push_back(value_type&& _Val) {
		_Nodeptr _Tmp = _create_node(iris::move(_Val));
		_Tmp->_hook(_Myimp._Myhead);
		++_Myimp._Mysize;
	}
#endif // __CXX_HASCXX0X__

	void pop_back() {
		_Nodeptr _node_to_delete = _Myimp._Myhead->_Prev;
		_erase(_node_to_delete);
	}

	void pop_front() {
		_Nodeptr _node_to_delete = _Myimp._Myhead->_Next;
		_erase(_node_to_delete);
	}

public:
	iterator erase(iterator _Pos) {
		iterator _ret = iterator(_Pos._Ptr->_Next);
		_erase(_Pos._Ptr);
		return _ret;
	}

private:

	void _erase(_Nodeptr _node_to_delete) {
		_node_to_delete->_unhook();
#if __CXX_HASCXX0X__
		_Getnodal().destroy(_node_to_delete);
#else
		_Getyal().destroy(iris::__addressof(_node_to_delete->_Myval));
#endif // __CXX_HASCXX0X__

		del_node(_node_to_delete);
		--_Myimp._Mysize;
	}

#if __CXX_HASCXX0X__
	template <typename... _Types>
	_Nodeptr _create_node(_Types&&... _Args) {
		_Nodeptr _newnode = get_node();
		try {
			_Getnodal().construct(_newnode, iris::forward<_Types>(_Args)...);
		}
		catch (...) {
			del_node(_newnode);
		}
		return _newnode;
	}
#else
	_Nodeptr _create_node(const value_type& _Val) {
		_Nodeptr _newnode = get_node();
		try {
			_Getyal().construct(iris::__addressof(_newnode->_Myval), _Val);
		}
		catch (...) {
			del_node(_newnode);
		}
		return _newnode;
	}
#endif // __CXX_HASCXX0X__

	void _initialize_dispatch(_Nodeptr _first, _Nodeptr _last) {
		for (; _first != _last; _first = _first->_Next) {
			push_back(_first->_Myval);
		}
	}
};
_IRIS_END_
#endif // _IRIS_LIST_