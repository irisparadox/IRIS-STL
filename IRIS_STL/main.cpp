#include <vector.h>
#include <vector>
#include <pair.h>
#include <utility>
#include <string>
#include <iostream>
#include <hash.h>
#include <list>
#include <list.h>
#include <unordered_map.h>
#include <unordered_map>

int main() {
	{
		iris::vector<int> testCases;
		for (int i = 0; i <= 1000; ++i) {
			testCases.push_back(i);
		}

		std::unordered_map<int, int> hashmap;
		int collisions = 0;

		for (const auto val : testCases) {
			int hashedValue = iris::XXH64(val);

			if (hashmap.count(hashedValue)) ++collisions;

			++hashmap[hashedValue];
		}
	}
	{
		iris::list<iris::list<int>> lists;
		iris::list<int> list = { 1, 2, 3 };

		lists.push_back(list);

		list.pop_back();

		long long hash = iris::XXH64(list);
	}
	{
		std::list<std::vector<int>> stdListVec;
		std::vector<int> stdvec = { 1, 2, 3 };
		stdvec.push_back(4);
		stdvec.push_back(5);

		stdListVec.push_front(stdvec);
	}
	{
		iris::vector<int> vec;
		vec.push_back(16);
		vec.push_back(32);
		vec.push_back(64);
		vec.push_back(128);
		vec.push_back(256);
		vec.push_back(512);
		vec.push_back(1024);

		iris::vector<bool> vec2;
		vec2.push_back(true);
		vec2.push_back(true);
		vec2.push_back(false);
		vec2.push_back(true);
		vec2.push_back(false);
		vec2.push_back(false);
		vec2.push_back(true);

		iris::pair<int, int> _Mypair(1, 2);
		iris::pair<int, int> _Mypair2(1, 2);

		bool is = (_Mypair == _Mypair2);

		std::cout << vec.front() << '\n';

		std::cout << vec[5] << '\n';

		vec.pop_back();

		iris::vector<int>::iterator it = vec.begin();

		it++;

		iris::vector<const char*> vec3(10, "abc");

		iris::list<int> list;
		iris::list<iris::vector<int>> listVec;

		list.push_back(5);
		list.push_front(10);
		list.push_back(20);
		list.push_front(30);

		listVec.push_front(vec);
		
		list.front();
		list.back();

		iris::vector<int> movevec(iris::move(vec));

		vec.push_back(10);
	}
	{
		int inputInt = 42;
		long long hashInt = iris::XXH64(inputInt);
		int input2 = 43;
		long long hashInt1 = iris::XXH64(input2);

		if (hashInt == hashInt1) return -1;
	}
	return 0;
}