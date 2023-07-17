#pragma ocne
#include "sort.h"
#include "../randomizer/random.h"
#include "../algorithms/is_sorted.h"
#include "../algorithms/shuffle.h"

namespace Sorting {
	template<typename ArrayType>
	class BogoSort : public Sort<ArrayType> {
	public:
		BogoSort(ArrayType& array)
			: Sort<ArrayType>(array) {

		}
        
        template<typename Func>
		void sort(Func cmp) {
            while (!Algorithms::is_sorted(this->m_Array, cmp)) {
                Algorithms::shuffle(this->m_Array);
            }
		}
	};
}
