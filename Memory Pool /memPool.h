#ifndef MEMPOOL_H_
#define MEMPOOL_H_

#include <iostream>
#include <vector>

template <typename T>
class memPool {
private:
	struct Block {
		Block* next;
	};

	std::vector<void*> poolStorage;
	Block* freeList;
	std::size_t blockSize;
	std::size_t poolSize;

public:
	using value_type = T;
	using size_type = std::size_t;
	using pointer = T*;
	using reference = T&;
	using const_ref = const T&;
	using const_pointer = const T*;

	memPool(size_type size) noexcept : blockSize(sizeof(T)), poolSize(size), freeList(nullptr) {
		expandPool();
	}

	~memPool() noexcept {
		for (void* ptr : poolStorage) {
			free(ptr);
		}
	}
	 
	template <typename U>
	memPool(const memPool<U>&) noexcept {}

	pointer addresses(reference obj) const noexcept {
		return &obj;
	}

	const_pointer addresses(const_ref obj) const noexcept {
		return &obj;
	}

	pointer allocate() {
		if (!freeList) {
			expandPool();
		}
		Block* block = freeList;
		freeList = freeList->next;
		//return block;
		return reinterpret_cast<pointer>(block);
	}

	void deallocate(pointer p) {
		//Block* block = static_cast<Block*>(p);
		Block* block = reinterpret_cast<Block*>(p);
		block->next = freeList;
		freeList = block;
	}

	template <typename... Args>
	void construct(pointer p, Args&&...args) {
		new((void*)p) T(std::forward<Args>(args)...);
	}

	void destroy(pointer p) {
		p->~T();
	}

	template <typename... Args>
	pointer newElement(Args&&... args) {
		pointer mem = allocate();
		construct(mem, std::forward<Args>(args)...);
		return mem;
	}

	void deleteElement(pointer p) {
		if (p) {
			destroy(p);
			deallocate(p);
		}
	}

private:
	void expandPool() {
		size_type size = blockSize > sizeof(Block*) ? blockSize : sizeof(Block*);
		void* newBlock = malloc(size * poolSize);
		if (!newBlock) {
			throw std::bad_alloc();
		}
		poolStorage.push_back(newBlock);

		for (size_type i = 0; i < poolSize; i++) {
			Block* block = reinterpret_cast<Block*>(static_cast<char*>(newBlock) + i * size);
			block->next = freeList;
			freeList = block;
		}
	}
};

#endif // !MEMPOOL_H_
