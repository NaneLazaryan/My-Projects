#ifndef ALLOCATOR_
#define ALLOCATOR_

#include <iostream>
#include <limits>

template <typename T>
class Allocator {
public:
	using value_type = T;
	using pointer = T*;
	using reference = T&;
	using const_reference = const T&;;
	using size_type = std::size_t;
	template<typename U>
	struct rebind { using other = Allocator<U>; };

	Allocator() noexcept {}
	Allocator(const Allocator&) noexcept {}


	template<typename U>
	Allocator(const Allocator<U>&) noexcept {}

	~Allocator() {}

	pointer allocate(size_type n) {
		T* alloc = (T*) ::operator new(n * sizeof(T));
		return alloc;
	}

	void deallocate(pointer p, size_type) {
		::operator delete(p);
	}

	void construct(pointer p, const reference value) {
		new((void*)p) T(value);  // placement new
	}

	void destroy(pointer p) {
		p->~T();
	}

	pointer addresses(reference obj) const noexcept {
		return &obj;
	}

	const pointer addresses(const_reference obj) const noexcept {
		return &obj;
	}

	size_type max_size() const noexcept {
		// maximum number of T objects that could fit in the system's addressable memory
		return std::numeric_limits<size_t>::max() / sizeof(T);
	}

	bool operator==(const Allocator&) const noexcept {
		return true;
	}

	bool operator!=(const Allocator&) const noexcept {
		return false;
	}

};

#endif // !ALLOCATOR_
