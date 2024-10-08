#include <iarray>
#include <iostream>

int main() {
	IRIS::iarray<int, 5> arr = { 1, 2, 3, 4, 5 };

	for (auto& val : arr) {
		val *= 4;
	}

	for (auto& val : arr) {
		std::cout << val << '\n';
	}

	return 0;
}