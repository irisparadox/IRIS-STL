#include <vector.h>
#include <vector>
#include <pair.h>
#include <utility>
#include <string>
#include <iostream>
#include <hash.h>

int main() {
	{
		IRIS::vector<int> vec;
		vec.push_back(16);
		vec.push_back(32);
		vec.push_back(64);
		vec.push_back(128);
		vec.push_back(256);
		vec.push_back(512);
		vec.push_back(1024);

		IRIS::vector<bool> vec2;
		vec2.push_back(true);
		vec2.push_back(true);
		vec2.push_back(false);
		vec2.push_back(true);
		vec2.push_back(false);
		vec2.push_back(false);
		vec2.push_back(true);

		IRIS::pair<int, int> _Mypair(1, 2);
		IRIS::pair<int, int> _Mypair2(1, 2);

		bool is = (_Mypair == _Mypair2);

		std::cout << vec.front() << '\n';

		std::cout << vec[5] << '\n';

		vec.pop_back();

		IRIS::vector<int>::iterator it = vec.begin();

		it++;

		IRIS::vector<const char*> vec3(10, "abc");
	}
	{
		int inputInt = 42;
		long long hashInt = IRIS::XXH64(inputInt);
		int input2 = 43;
		long long hashInt1 = IRIS::XXH64(input2);

		if (hashInt == hashInt1) return -1;
	}
	return 0;
}