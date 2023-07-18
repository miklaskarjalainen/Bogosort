#include <cstdio>
#include <cassert>

#include "algorithms/to_string.h"
#include "containers/array.h"
#include "sorting/bogosort.h"
#include "randomizer/array_builder.h"

int main() {
	auto my_array = Randomizer::RandomArrayBuilder<float, 10>()
		.set_seed(69420)
		.set_min_element(-55.f)
		.set_max_element(55.f)
		.build();

	printf("Start Array: ");
	my_array.for_each(
		[](const auto& i) {
			printf("%s ", Algorithms::to_string(i).c_str());
		}
	);
	printf("\n");

	auto bogosort = Sorting::BogoSort(my_array);
	bogosort.sort([](auto a, auto b) -> bool {
		return a>b;
	});

	printf("Sorted Array: ");
	my_array.for_each(
		[](const auto& i) {
			printf("%s ", Algorithms::to_string(i).c_str());
		}
	);
	printf("\n");
	
	return 0;
}


