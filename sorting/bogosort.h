#pragma ocne
#include "../randomizer/random.h"
#include "../algorithms/is_sorted.h"
#include "../algorithms/shuffle.h"

namespace BogoSort {
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

