#include "containers/string.h"
#include "containers/array.h"
#include "sorting/bogosort.h"
#include "randomizer/array_builder.h"
#include "io/print.h" 

#define SEED 69420
#define RANDOM_ARRAY_LENGTH 12

int main() {
	auto my_array = BogoSort::RandomArrayBuilder<float, RANDOM_ARRAY_LENGTH>()
		.set_seed(SEED)
		.set_min_element(-55.f)
		.set_max_element(55.f)
		.build();

	BogoSort::Print::write("Start Array: ");
	my_array.for_each(
		[](const auto& i) {
			BogoSort::Print::write(BogoSort::to_string(i).c_str());
		}
	);
	BogoSort::Print::write("\n");

	auto bogosort = BogoSort::BogoSorter(my_array);
	bogosort.sort([](auto a, auto b) -> bool {
		return a>b;
	});

	BogoSort::Print::write("Sorted Array: ");
	my_array.for_each(
		[](const auto& i) {
			BogoSort::Print::write(BogoSort::to_string(i).c_str());
		}
	);
	BogoSort::Print::write("\n");
	
	return 0;
}


