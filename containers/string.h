#pragma once

typedef unsigned long long size_t;
#include <string.h>
#include <stdio.h>

#include "iterator.h"

namespace BogoSort {

    class String {
    public:
        String() { 
            reserve(DefaultLength);
        }
        String(const char* str) {
            m_Length = strlen(str);
            reserve(m_Length);
            strcpy(m_Buffer, str);
        }
        ~String() {
            if (m_Buffer)
                delete[] m_Buffer;
        }

        const char* c_str() const {
            return m_Buffer;
        }

        size_t size() const {
            return m_Length;
        }

        size_t capacity() const {
            return m_Capacity;
        }

        void push(char c) {
            // Needs a resize
            if (m_Length>= m_Capacity) {
                reserve(m_Capacity * 2);
            }

            m_Buffer[m_Length++] = c;
            m_Buffer[m_Length] = '\0'; // FIXME: stupid fix actually, shouldn't be needed xd
        }

        Iterator<char> begin() const {
			return Iterator(&m_Buffer[0]); 
		}

		Iterator<char> end() const { 
			return Iterator(&m_Buffer[m_Length]);
		}

        void push_str(const String& other) {
            for (const auto& c : other) {
                push(c);
            }
            m_Buffer[m_Length] = '\0';
        }
    
        void reserve(size_t capacity) {
            if (capacity == 0) {
                capacity = DefaultLength;
            }
            if (capacity == m_Capacity)
                return;

            char* new_buffer = new char[capacity];
            memset(new_buffer, '\0', sizeof(capacity));
            
            if (m_Buffer) {
                strcpy(new_buffer, m_Buffer);
                delete[] m_Buffer;
            }

            m_Capacity = capacity;
            m_Buffer = new_buffer;
        }

        // reverses the string, duh
        void reverse() {
            for (int i = 0, j = size() - 1; i < j; i++, j--) {
                char temp = m_Buffer[i];
                m_Buffer[i] = m_Buffer[j];
                m_Buffer[j] = temp;
		    }
        }


    private:
        size_t m_Length = 0; // doesn't include null terminator
        size_t m_Capacity = 0;
        char* m_Buffer = nullptr;

        const size_t DefaultLength = 8;
    };

}
