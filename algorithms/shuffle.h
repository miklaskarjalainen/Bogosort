#pragma once

namespace Algorithms {
    template<typename ArrayType> 
    void shuffle(ArrayType& array) {
        static auto rand = Randomizer::Random();

        for (int i = array.size() - 1; i > 0; i--) {
            int j = rand.rand() % (i + 1);

            auto temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }
}
