#include <iarray>
#include <iostream>
#include <vector>
#include <ivector>
#include <array>
#include <ilist>
#include <icomplex>
#include <complex>

int main() {

	IRIS::complex<float> c(1.0f, 2.0f);
	IRIS::complex<float> z = c;

	IRIS::complex<float> w = c / z;

	IRIS::get<1, float>(w) = 5;
	std::cout << IRIS::abs(w) << '\n';

	std::complex<float> a(1, 5);

	std::cout << w.arg() << '\n';
	std::cout << std::arg(a) << '\n';

	while (1);

	/*
	IRIS::ilist<int> list;
	IRIS::ilist<IRIS::ivector<int>> listVec;

	IRIS::ivector<int> newVec = { 1, 2, 3 };
	listVec.push_back(newVec);

	list.push_back(5);
	list.push_front(10);

	std::cout << list.front() << '\n';
	std::cout << list.back() << '\n';
	std::cout << list.size() << '\n';

	list.clear();
	/*

	/*IRIS::ivector<int> vec = {1, 2, 3};
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

	vec.clear();

	std::cout << vec.capacity() << '\n';
	std::cout << vec.size() << '\n';

	IRIS::ivector<int> vec1 = { 1, 2, 3, 4 };
	IRIS::ivector<int> vec2 = { 1, 2, 3 };

	if (vec1 == vec2) std::cout << "Yes\n";

	it = vec1.begin();

	it += 3;

	it = vec1.erase(it);
	
	if (vec1 == vec2) std::cout << "Yes\n";*/
	
	return 0;
}