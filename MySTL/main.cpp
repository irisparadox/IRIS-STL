#include <iarray>
#include <vector>
#include <array>

int main() {
	std::array<int, 5> stdArr = { 1, 2, 3, 4, 5 };

	IRIS::iarray<int, 5> arr = { 1, 2, 3, 4, 5 };

	return 0;
}