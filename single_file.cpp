// Under linux we use assembly to call print via a syscall so include is not needed :) 
#if defined(__linux__) && defined(__x86_64__)
    #define SYSCALL_WRITE 1
#else
    #include <cstdio> 
#endif

typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;
typedef unsigned long long size_t;

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

    template<typename T> 
    void swap(T& i, T& j) {
        auto temp = i;
        i = j;
        j = temp;
    }

    template<typename ArrayType> 
    void shuffle(ArrayType& array) {
        static auto rand = Random();

        for (int i = array.size() - 1; i > 0; i--) {
            int j = rand.rand() % (i + 1);
            swap(array[i], array[j]);
        }
    }

    template<typename ArrayType, typename Func> 
    bool is_sorted(const ArrayType& array, Func&& cmp) {
        for (int i = 1; i < array.size(); i++) {
            if (cmp(array[i - 1], array[i])) {
                return false;
            }
        }
        return true;
    }

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

    class String {
    public:
        String() { 
            reserve(DefaultLength);
        }
        String(const char* str) {
            m_Length = strlen(str);
            reserve(m_Length);
            memcpy(m_Buffer, str, m_Length);
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
            if ((m_Length-1) >= m_Capacity) {
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

        String to_string(int number) {
        auto str = String("");

        // Check if the number is negative
		int isNegative = 0;
		if (number < 0) {
			isNegative = 1;
			number = -number;
		}

		// Convert each digit to character and store in reverse order
		do {
			str.push((number % 10) + '0');
			number /= 10;
		} while (number != 0);

		// Add negative sign if necessary
		if (isNegative) {
            str.push('-');
        }

        str.reverse();
        return str;
    }

    String to_string(float number) {
        auto str = String("");

        // Check for negative number
        bool is_negative = false;
        if (number < 0) {
            is_negative = true;
            number = -number;
        }

        // Extract the integer part
        int integerPart = (int)number;

        // Convert the integer part to a string
        int decimalCount = 0;
        do {
			str.push((integerPart % 10) + '0');
			integerPart /= 10;
            decimalCount++;
		} while (integerPart > 0);

        if (is_negative) {
            str.push('-');
        }

        str.reverse();

        // Add decimal point
        str.push('.');

        // Extract the decimal part
        float decimalPart = number - (int)number;
        // Convert the decimal part to a string
        do {
            decimalPart *= 10;
            int digit = (int)decimalPart;
            str.push('0' + digit);
            decimalPart -= digit;
            decimalCount++;
        } while (decimalCount < 10 && decimalPart != 0);

        return str;
    }

    template<typename T, size_t capacity>
	class Array {
	public:
		Array() = default;
		~Array() = default;
	
		size_t size() const { return capacity; }
	
		Iterator<T> begin() {
			return Iterator(&m_Array[0]); 
		}

		Iterator<T> end() { 
			return Iterator(&m_Array[size()]);
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

        class Print {
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
        static void write(const char* print, Args... args) {
            write(format_arg(print, args...).c_str());
        }

    private:
        Print() = delete;
        ~Print() = delete;
    };

    // based on: https://en.wikipedia.org/wiki/Permuted_congruential_generator
	class Random {
	public:
		Random() {};
		~Random() {};
		
		void set_seed(unsigned int seed) {
			m_Seed = seed + Increment;
			rand();
		}

		uint32_t rand()
		{
			uint64_t x = m_Seed;
			unsigned count = (unsigned)(x >> 59);		// 59 = 64 - 5

			m_Seed = x * Multiplier + Increment;
			x ^= x >> 18;								// 18 = (64 - 27)/2
			return rotr32((uint32_t)(x >> 27), count) % RandMax;	// 27 = 32 - 5
		}

		float randf() {
			return ((float)rand() / RandMax);
		}

        // (inclusive)
		// https://stackoverflow.com/questions/12657962/how-do-i-generate-a-random-number-between-two-variables-that-i-have-stored
        int rand_range(const int& min, const int& max) {
			return (int)rand()%(max-min+1)+min;
		}

        float rand_range(float min, float max) {
            return randf() * (max - min) + min;
        }

		const uint32_t RandMax = 0x7FFF;
	private:
		static uint32_t rotr32(uint32_t x, unsigned r)
		{
			return x >> r | x << (-r & 31);
		}
		
		uint64_t m_Seed = 0x4d595df4d0f33173;
		const uint64_t Multiplier = 6364136223846793005u;
		const uint64_t Increment  = 1442695040888963407u;
	};

    template<typename T, size_t array_size>
	class RandomArrayBuilder {
	public:
		RandomArrayBuilder() {};
		~RandomArrayBuilder() {};

		
		Array<T, array_size> build() {
			auto array = Array<T, array_size>();
			for (auto& i : array) {
				i = m_RandomGenerator.rand_range(m_Min, m_Max);
			}
			return array;
		}

		RandomArrayBuilder& set_seed(unsigned int seed) {
			m_RandomGenerator.set_seed(seed);
			return *this;
		}

		RandomArrayBuilder& set_min_element(const T& min) {
            m_Min = min;
			return *this;
		}
		
		RandomArrayBuilder& set_max_element(const T& max) {
            m_Max = max;
			return *this;
		}

	private:
		T m_Max, m_Min;
		Random m_RandomGenerator;

	};

	template<typename ArrayType>
	class BogoSorter {
    public:
        BogoSorter() = default;
        BogoSorter(ArrayType& array): m_Array(array) {}
        ~BogoSorter() = default;
        
        template<typename Func>
        void sort(Func cmp) {
            while (!is_sorted(this->m_Array, cmp)) {
                shuffle(this->m_Array);
            }
        }
    
    private:
        ArrayType& m_Array;
    };
}

#define SEED 69420
#define RANDOM_ARRAY_LENGTH 11

int main() {
	auto my_array = BogoSort::RandomArrayBuilder<float, RANDOM_ARRAY_LENGTH>()
		.set_seed(SEED)
		.set_min_element(-55.f)
		.set_max_element(55.f)
		.build();

	BogoSort::Print::write("Start Array: ");
	my_array.for_each(
		[](const auto& i) {
			BogoSort::Print::write("{} ", i);
		}
	);
	BogoSort::Print::write("\n");

	auto bogosort = BogoSort::BogoSorter(my_array);
	bogosort.sort([](auto a, auto b) -> bool {
		return a>b;
	});

	BogoSort::Print::write("Sorted Array: ");
	my_array.for_each(
		[](const auto& i) {
			BogoSort::Print::write("{} ", i);
		}
	);
	BogoSort::Print::write("\n");
	
	return 0;
}
