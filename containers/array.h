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
	
		Containers::Iterator<T> begin() {
			return Containers::Iterator(&m_Array[0]); 
		}

		Containers::Iterator<T> end() { 
			return Containers::Iterator(&m_Array[size()]);
		}

		T& operator[](size_t idx) {
			return m_Array[idx]; 
		}

		const T& operator[](size_t idx) const {
			return m_Array[idx]; 
		}

		template<typename Func>
		void for_each(Func&& func) const {
			for (const auto& i : m_Array) {
				func(i);
			}
		}

	private:
		T m_Array[capacity];

	};

}
