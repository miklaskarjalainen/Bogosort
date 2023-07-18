#pragma once

typedef unsigned long long size_t;

#include "iterator.h"

namespace Containers {

	template<typename T, size_t capacity>
	class Array {
	public:
		Array() = default;
		~Array() = default;
	
		size_t size() const { return capacity; }
	
		Container::Iterator<T> begin() const {
			return Container::Iterator(&m_Array[0]); 
		}

		Container::Iterator<T> end() const { 
			return Container::Iterator(&m_Array[size()]);
		}

		T& operator[](size_t idx) {
			return m_Array[idx]; 
		}

		const T& operator[](size_t idx) const {
			return m_Array[idx]; 
		}

	private:
		T m_Array[capacity];

	};

}
