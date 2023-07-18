#include <cstdio>
#include <cassert>

#include "containers/array.h"
#include "sorting/bogosort.h"
#include "randomizer/array_builder.h"

int main() {
	auto my_array = Randomizer::RandomArrayBuilder<unsigned char, 10>()
		.set_seed(69420)
		.set_min_element(0)
		.set_max_element(255)
		.build();

	printf("Start Array: ");
	for (const auto& i : my_array) {
		printf("%i ", i);
	}
	printf("\n");

	auto bogosort = Sorting::BogoSort(my_array);
	bogosort.sort([&](auto a, auto b) -> bool {
		return a>b;
	});

	printf("Sorted Array: ");
	for (const auto& i : my_array) {
		printf("%i ", i);
	}
	printf("\n");

	return 0;
}


