#pragma once

// Under linux we use assembly to call print via a syscall so include is not needed :) 
#if defined(__linux__) && defined(__x86_64__)
    #define SYSCALL_WRITE 1
#else
    #include <cstdio> 
#endif

#include "../algorithms/string.h"
#include "../containers/string.h"

namespace BogoSort {

    class Print {
    public:
        static void write(const char* print) {
            #ifndef __linux__ 
                printf("%s", print);
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

        

        template<typename ...Args>
        static void formatted(const char* format, Args... args) {
            format_arg(format, args...);
        }

    private:
        template<typename T>
        static void format_arg(const char* format, const T& arg) {
            printf("%s ", to_string(arg).c_str());
        }

        template<typename T, typename... Args>
        static void format_arg(const char* format, const T& arg, Args... args) {
            int i = 0;
            int len = strlen(format);
            while (i < len) {
                char cur = format[i++];
                char next = (i < len) ? format[i++] : '\0';
                if (cur == '{' && next == '}') {
                    printf("%s ", to_string(arg).c_str());
                    format_arg((format + i), args...);
                    return;
                }
                else {
                    printf("%c", cur);
                }
            }
            
        }

        Print() = delete;
        ~Print() = delete;
    };

}
