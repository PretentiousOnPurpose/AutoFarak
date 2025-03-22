#include <iostream>
#include "afdtype.hpp"
using namespace std;

int main() {
	double pi = 3.14159;
	double pi_l[] = {0, 2, 4, 6, 8, 10, 12};
	
	auto x1 = afdtype::var(&pi_l[0], 7);
	auto x2 = afdtype::var(&pi_l[0], 7);

	auto x3 = afdtype::pow(x1, 2);

	x3.print();

	
	return 0;
}
