#include <vector.h>
#include <vector>
#include <pair.h>
#include <utility>
#include <string>
#include <iostream>
#include <hash.h>
#include <list>
#include <list.h>

int main() {
	{
		IRIS::list<IRIS::list<int>> lists;
		IRIS::list<int> list = { 1, 2, 3 };

		lists.push_back(list);

		list.pop_back();
	}
	{
		std::list<std::vector<int>> stdListVec;
		std::vector<int> stdvec = { 1, 2, 3 };
		stdvec.push_back(4);
		stdvec.push_back(5);

		stdListVec.push_front(stdvec);
	}
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

		IRIS::list<int> list;
		IRIS::list<IRIS::vector<int>> listVec;

		list.push_back(5);
		list.push_front(10);
		list.push_back(20);
		list.push_front(30);

		listVec.push_front(vec);
		
		list.front();
		list.back();

		IRIS::vector<int> movevec(IRIS::move(vec));

		vec.push_back(10);
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