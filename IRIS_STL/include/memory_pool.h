#ifndef _IRIS_MEMORY_POOL_
#define _IRIS_MEMORY_POOL_

#include <cxx_config.h>
#include <mem_operators.h>

_IRIS_BEGIN_
class memory_pool {
public:
	memory_pool(size_t _Sizeof, size_t _Num) : _Blocksize(_Sizeof), _Poolsize(_Num) {
		_Poolstart = static_cast<char*>(::operator new(_Poolsize * _Blocksize));
		_Initialize_freelist();
	}

	~memory_pool() {
		::operator delete(_Poolstart);
	}

	void* allocate() {
		if (!_Freelist) _Expand();

		Block* _Myalloc = _Freelist;
		_Freelist = _Freelist->_Next;
		return _Myalloc;
	}

	void deallocate(void* _Ptr) {
		if (!_Ptr) return;

		Block* _Myfree = static_cast<Block*>(_Ptr);
		_Myfree->_Next = _Freelist;
		_Freelist = _Myfree;
	}

private:

	// A block of memory
	struct Block {
		// Next memory block
		Block* _Next;
	};

	Block* _Freelist;
	char*  _Poolstart;
	size_t _Blocksize;
	size_t _Poolsize;

private:
	void _Initialize_freelist() {
		_Freelist = reinterpret_cast<Block*>(_Poolstart);
		Block* _current = _Freelist;

		for (size_t i = 1; i < _Poolsize; ++i) {
			_current->_Next = reinterpret_cast<Block*>(_Poolstart + (i * _Blocksize));
			_current = _current->_Next;
		}

		_current->_Next = nullptr;
	}

	void _Expand() {
		size_t _Newpool_size = (_Poolsize < 2) ? 1 : _Poolsize + (_Poolsize / 2);
		char* new_pool = static_cast<char*>(::operator new(_Newpool_size * _Blocksize));

		Block* new_freelist = reinterpret_cast<Block*>(new_pool);
		Block* current_block = new_freelist;

		Block* old_freelist = _Freelist;
		while (old_freelist) {
			current_block->_Next = old_freelist->_Next;
			current_block = current_block->_Next;
			old_freelist = old_freelist->_Next;
		}

		_Poolstart = new_pool;
		_Poolsize = _Newpool_size;

		_Initialize_freelist();
	}
};
_IRIS_END_
#endif // _IRIS_MEMORY_POOL_
