#pragma once
#include "../randomizer/random.h"

namespace BogoSort {
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
}
