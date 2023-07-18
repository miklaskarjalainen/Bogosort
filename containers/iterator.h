#pragma once

namespace Container {
    // https://www.internalpointers.com/post/writing-custom-iterators-modern-cpp
    template<typename T>
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
}