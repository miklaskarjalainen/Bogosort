#pragma once

// Under linux we use assembly to call print via a syscall so include is not needed :) 
#if defined(__linux__) && defined(__x86_64__)
    #define SYSCALL_WRITE 1
#else
    #include <cstdio> 
#endif

#include "../algorithms/string.h"

namespace BogoSort {

    class Print {
    public:
        static void write(const char* print) {
            #ifndef __linux__ 
                printf("%s\n", print);
            #else
                size_t ret;
                int fd = 1;
                size_t size = strlen(print);
                asm volatile
                (
                        "syscall"
                        : "=a" (ret)
                        : "0"(SYSCALL_WRITE), "D"(fd), "S"(print), "d"(size)
                        : "rcx", "r11", "memory"
                );
            #endif
        }

    private:
        Print() = delete;
        ~Print() = delete;
    };

}
