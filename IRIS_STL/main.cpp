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
#include <random>

int main() {
	{
		iris::unordered_map<int, int> map;
		map.insert({ 1, 1 });
		map.insert({ 1, 10 });
		map.insert({ 13523, 2 });
		map[1];
		map[5];
		map[5] = 10;
	}
	return 0;
}