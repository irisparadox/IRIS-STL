#include <vector.h>
#include <vector>
#include<pair.h>
#include <utility>
#include <string>

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
	}
	{
		std::pair<int, int> _Mypair;
		IRIS::pair<bool, int> _Mypair2;
		IRIS::pair<std::string, std::string> pair("hola", "mundo");
	}
	return 0;
}