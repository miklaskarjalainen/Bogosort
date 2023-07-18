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
            size_t i = 0;
            size_t len = strlen(format);

            while (i < len) {
                if (format[i] == '{' && i + 1 < len) {
                    char next = format[++i];
                    if (next == '}') {
                        i++;
                        print_arg(args);
                    }
                    else {
                        printf("{");
                    }
                }
                else {
                    printf("%c", format[i]);
                    i++;
                }
            }
        }

    private:
        template<typename T>
        static void print_arg(const T& arg) {
            printf("%s ", to_string(arg).c_str());
        }

        template<typename T, typename... Args>
        static void print_arg(const T& arg, Args... args) {
            printf("%s ", to_string(arg).c_str());
            print_arg(args...);
        }

        Print() = delete;
        ~Print() = delete;
    };

}
