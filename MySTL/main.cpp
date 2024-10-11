#include <iarray>
#include <iostream>
#include <vector>
#include <ivector>

int main() {
	IRIS::ivector<int> vec;
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);
	vec.push_back(4);
	vec.push_back(5);
	vec.push_back(6);
	vec.push_back(7);
	vec.push_back(8);
	vec.push_back(9);
	vec.push_back(10);
	vec.push_back(11);
	vec.push_back(12);
	vec.push_back(13);
	vec.push_back(14);
	vec.push_back(15);

	std::cout << vec.capacity() << '\n';

	return 0;
}