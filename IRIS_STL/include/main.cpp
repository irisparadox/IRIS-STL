#include "vector.h"

int main() {
	{
		IRIS::vector<int> vec(5);
		vec.push_back(1);
		vec.push_back(2);
		vec.push_back(100);
	}

	return 0;
}