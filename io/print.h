#pragma once

// under linux we use syscalls in assembly, so we don't even need to include cstdio.
#ifndef __linux__ 
    #include <cstdio> 
#else
    #define SYSCALL_WRITE 1
#endif

namespace BogoSort {

    class Print {
    public:
        void write(const char* print) {
            #ifndef __linux__ 
                printf("%s\n", print);
            #else
                size_t ret;
                int fd = 1;
                size_t size = 13;
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
