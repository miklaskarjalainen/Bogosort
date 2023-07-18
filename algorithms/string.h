#pragma once

namespace BogoSort {
	size_t strlen(const char* str) {
		const char* s = str;
		while (*s)
			++s;
        
		return s - str;
	}

    char* strcpy(char* dest, const char* source) {
        char* d = dest;

        // Copy characters from source to destination
        while (*source) {
            *d = *source;
            ++d;
            ++source;
        }

        // Add null terminator at the end
        *d = '\0';

        return dest;
    }

    char* memcpy(char* dest, const char* src, size_t size) {
        // Copy bytes from source to destination
        for (size_t i = 0; i < size; ++i) {
            dest[i] = src[i];
        }
        return dest;
    }

    char* memset(char* dest, int value, size_t size) {
        unsigned char* p = (unsigned char*)dest;
        unsigned char byteValue = (unsigned char)value;

        for (size_t i = 0; i < size; ++i) {
            p[i] = byteValue;
        }
        return dest;
    }
}
