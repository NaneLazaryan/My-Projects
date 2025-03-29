#pragma once

#include <iostream>
#include <optional>

#pragma pack(push, 1)

struct nullopt_t {
	constexpr explicit nullopt_t(int) {  }
};

constexpr nullopt_t nullopt{ 0 };

template <typename T>
class Optional {
private:
	bool m_has_value;
	alignas(T) unsigned char storage[sizeof(T)];
public:
	Optional() noexcept : m_has_value(false) {
		*this = nullopt;
	}

	Optional(nullopt_t) : m_has_value(false) {}

	template <typename... Args>
	explicit Optional(Args&&... args) : m_has_value(true) { 
		new(storage) T(std::forward<Args>(args)...);
	}

	// copy constructor
	Optional(const Optional& other) : m_has_value(other.m_has_value) { 
		if (other.m_has_value) {
			new(storage) T(*reinterpret_cast<const T*>(other.storage));
		}
	}

	// move constructor
	Optional(Optional&& other) noexcept : m_has_value(other.m_has_value) { 
		if (other.m_has_value) {
			new (storage) T(std::move(*reinterpret_cast<T*>(other.storage)));
			other.m_has_value = false;
		}
	}

	~Optional() {
		reset();
	}

	Optional& operator=(nullopt_t) {
		m_has_value = false;
		return *this;
	}

	// copy assignment
	Optional& operator=(const Optional& other) {
		if (this != &other) {
			reset();
			if (other.m_has_value) {
				new(storage) T(*reinterpret_cast<const T*>(other.storage));
				m_has_value = true;
			}
		}
		return *this;
	}

	// move assignmet
	Optional& operator=(Optional&& other) noexcept {
		if (this != &other) {
			reset();
			if (other.m_has_value) {
				new(storage) T(std::move(*reinterpret_cast<T*>(other.storage)));
				m_has_value = true;
			}
			other.m_has_value = false;
		}
		return *this;
	}

	bool has_value() const noexcept {
		return m_has_value;
	}

	T* operator->() {
		if (!m_has_value) throw std::bad_optional_access();
		return reinterpret_cast<T*>(storage);
	}

	const T* operator->() const {
		if (!m_has_value) throw std::bad_optional_access();
		return reinterpret_cast<T*>(storage);
	}

	T& operator*() {
		if (!m_has_value) throw std::bad_optional_access();
		return *reinterpret_cast<T*>(storage);
	}

	const T& operator*() const {
		if (!m_has_value) throw std::bad_optional_access();
		return *reinterpret_cast<T*>(storage);
	}

	T& value() {
		if (m_has_value) return *reinterpret_cast<T*>(storage);
		throw std::bad_optional_access();
	}

	const T& value() const {
		if (m_has_value) return *reinterpret_cast<T*>(storage);
		throw std::bad_optional_access();
	}

	template <typename U>
	T value_or(U&& default_value) const {
		if (m_has_value) {
			return *reinterpret_cast<const T*>(storage); 
		}
		return static_cast<T>(std::forward<U>(default_value));
	}

	void reset() noexcept {

		if (m_has_value) {
			if (!std::is_trivially_destructible_v<T>)
				reinterpret_cast<T*>(storage)->~T();
			m_has_value = false;
		}
	}
};

#pragma pack(pop)