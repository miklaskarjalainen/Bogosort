#pragma once
#include "random.h"

namespace BogoSort {

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
}