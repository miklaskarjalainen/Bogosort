#pragma once

namespace Algorithms {
    template<typename T> 
    void swap(T& i, T& j) {
        auto temp = i;
        i = j;
        j = temp;
    }
}
