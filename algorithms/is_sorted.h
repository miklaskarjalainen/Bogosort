#pragma once 

namespace Algorithms {
    template<typename ArrayType, typename Func> 
    bool is_sorted(const ArrayType& array, Func&& cmp) {
        for (int i = 1; i < array.size(); i++) {
            if (cmp(array[i - 1], array[i])) {
                return false;
            }
        }
        return true;
    }
}
