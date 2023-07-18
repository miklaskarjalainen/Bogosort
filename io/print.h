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
        template<typename ...Args>
        static void write(const char* print, Args... args) {
            write(format_arg(print, args...).c_str());
        }

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

private:
        template<typename T>
        static String format_arg(const char* format, const T& arg) {
            auto output = String();

            const char* ptr = format;
            int len = strlen(format);
            while (ptr[0] != '\0') {
                if (ptr[0] == '{' && ptr[1] == '}') {
                    ptr++; ptr++;
                    output.push_str(to_string(arg).c_str());
                }
                else {
                    output.push(*ptr);
                    ptr++;
                }
            }

            return output;
        }

        template<typename T, typename... Args>
        static String format_arg(const char* format, const T& arg, Args... args) {
            auto output = String();
            
            const char* ptr = format;
            int len = strlen(format);
            while (ptr[0] != '\0') {
                if (ptr[0] == '{' && ptr[1] == '}') {
                    ptr++; ptr++;
                    output.push_str(to_string(arg).c_str());
                    output.push_str(format_arg(ptr, args...));
                    return output;
                }
                else {
                    output.push(*ptr);
                    ptr++;
                }
            }

            return output;
        }

        Print() = delete;
        ~Print() = delete;
    };

}
