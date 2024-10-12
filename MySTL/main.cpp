#include <iarray>
#include <iostream>
#include <vector>
#include <ivector>
#include <array>

int main() {
	IRIS::ivector<int> vec;
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);
	vec.push_back(4);

	std::cout << vec.front() << '\n';
	std::cout << vec.back() << '\n';

	std::cout << vec.capacity() << '\n';
		
	return 0;
}