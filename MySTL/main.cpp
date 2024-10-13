#include <iarray>
#include <iostream>
#include <vector>
#include <ivector>
#include <array>

int main() {
	IRIS::ivector<int> vec = { 1, 2, 3 };
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);
	vec.push_back(4);
	
	std::cout << vec[3] << '\n';

	std::cout << "Evaluating vector\n";

	for (auto& val : vec) {
		std::cout << val;
	}

	IRIS::ivector<int>::iterator it = vec.begin();

	unsigned int i = 0;
	while (it != vec.end()) {
		if (i == 3)
			it = vec.insert(it, 87);
		++it;
		++i;
	}

	std::cout << '\n';

	std::cout << vec[3] << '\n';

	std::cout << vec.front() << '\n';
	std::cout << vec.back() << '\n';

	std::cout << vec.capacity() << '\n';
		
	return 0;
}