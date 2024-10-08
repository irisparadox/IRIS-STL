#include <iarray>
#include <vector>
#include <array>

int main() {
	std::array<int, 5> stdArr;
	IRIS::iarray<int, 5> arr;
	int a = arr.size();
	int b = stdArr.size();

	stdArr.at(5);

	return 0;
}