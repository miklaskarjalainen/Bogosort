#pragma once

typedef unsigned long long size_t;

namespace Containers {

	template<typename T, size_t capacity>
	class Array {
	public:
		Array() = default;
		~Array() = default;
	
		// https://www.internalpointers.com/post/writing-custom-iterators-modern-cpp
		class Iterator {
		public:
			Iterator(T* ptr)
				: m_Ptr(ptr) {}
			~Iterator() = default;

			// Operators
			T& operator*() const { return *m_Ptr; }
			T* operator->() const { return m_Ptr; }
			Iterator& operator++() { m_Ptr++; return *this; } // prefix
			Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; } // postfix
			friend bool operator== (const Iterator& a, const Iterator& b) { return a.m_Ptr == b.m_Ptr; };
    		friend bool operator!= (const Iterator& a, const Iterator& b) { return a.m_Ptr != b.m_Ptr; };     

		private:
			T* m_Ptr = nullptr;
		};

		size_t size() const { return capacity; }
	
		Iterator begin() {
			return Iterator(&m_Array[0]); 
		}

		Iterator end()   { 
			return Iterator(&m_Array[size()-1]);
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
