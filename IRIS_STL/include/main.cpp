#include <vector.h>
#include <vector>
#include <pair.h>
#include <utility>
#include <string>
#include <iostream>

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
	}
	return 0;
}