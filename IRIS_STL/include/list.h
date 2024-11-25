#ifndef _IRIS_LIST_
#define _IRIS_LIST_

#include <cxx_config.h>
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
	_Node(_Args&&... _Myargs) : _Myval(IRIS::forward<_Args>(_Myargs)...) {}
#endif // __CXX_HASCXX0X__

	static void swap(_Noderef _Left, _Noderef _Right) throw() {
		using IRIS::swap;
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
		using IRIS::swap;
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
		_Node::_Freenode(_Getnodal(), _Myimp._Myhead);
		_Myimp._Mysize = 0;
	}

	void _init() {
		_Myimp._Myhead = _Node::_Buyhead(_Getnodal());
	}
};

template <typename _Ty, typename _Al = IRIS::allocator<_Ty>>
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

protected:
	using _Mybase::_Myimp;
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

	~list() {}

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
	void push_back(const value_type& _Val) {
		_Nodeptr _newnode = _Myimp.allocate(1);
		_Myimp.construct_in_place(_newnode->_Myval, _Val);
		_place_back(_newnode);
		++_Myimp._Mysize;
	}

private:
	void _emplace_empty(_Nodeptr _Pnode) {
		_Myimp._Myhead->_Next = _Pnode;
		_Myimp._Myhead->_Prev = _Pnode;
		_Pnode->_Next = _Myimp._Myhead;
		_Pnode->_Prev = _Myimp._Myhead;
	}

	void _place_back(_Nodeptr _Pnode) {
		if (empty()) _emplace_empty(_Pnode);
		else {
			_Pnode->_Prev = _Myimp._Myhead->_Prev;
			_Pnode->_Next = _Myimp._Myhead;
			_Myimp._Myhead->_Prev->_Next = _Pnode;
			_Myimp._Myhead->_Prev = _Pnode;
		}
	}
};
_IRIS_END_
#endif // _IRIS_LIST_
