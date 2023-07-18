#pragma once

typedef unsigned int       uint32_t;
typedef unsigned long long uint64_t;

namespace Randomizer {

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
}
