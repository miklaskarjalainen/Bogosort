#include <cstdio>

#include "containers/array.h"
#include "sorting/bogosort.h"
#include "randomizer/array_builder.h"

int main() {

	auto my_array = Randomizer::RandomArrayBuilder<unsigned char, 12>()
		.set_seed(69420)
		.set_min_element(0)
		.set_max_element(255)
		.build();

	printf("Starting: \n");
	for (auto i : my_array) {
		printf("%u ", i);
	}
	printf("\n");

	auto bogosort = Sorting::BogoSort<decltype(my_array)>(my_array);
	bogosort.sort([](unsigned char a, unsigned char b) -> int {
		return a-b;
	});

	printf("Sorted: \n");
	for (auto i : my_array) {
		printf("%u ", i);
	}
	printf("\n");

	return 0;
}


