#pragma once

namespace Randomizer {
	class Random {
	public:
		Random() {};
		~Random() {};
		
		void set_seed(unsigned int seed) {
			m_Seed = seed;
		}
		// https://stackoverflow.com/questions/6417113/c-custom-random-function
		int rand() {
			m_Seed = m_Seed * 1664525 + 1013904223;
   			return m_Seed >> 24;
		}
        // (inclusive)
		// https://stackoverflow.com/questions/12657962/how-do-i-generate-a-random-number-between-two-variables-that-i-have-stored
        int rand_range(const int& min, const int& max) { return rand() % (max-min+1) + 1; }
        float rand_range(float min, float max) {
            const float MaxFloatNumber = 40.0000000000000000;
            return ((float)rand() / MaxFloatNumber) * (max - min) + min;
        }

        

	private:
		unsigned int m_Seed = 1664525;
	};
}
