#pragma ocne
#include "../randomizer/random.h"
#include "../algorithms/is_sorted.h"
#include "../algorithms/shuffle.h"

namespace Sorting {
	template<typename ArrayType>
	class BogoSort {
	public:
        BogoSort() = default;
		BogoSort(ArrayType& array): m_Array(array) {}
        ~BogoSort() = default;
        
        template<typename Func>
		void sort(Func cmp) {
            while (!Algorithms::is_sorted(this->m_Array, cmp)) {
                Algorithms::shuffle(this->m_Array);
            }
		}
    
    private:
        ArrayType& m_Array;
	};
}

