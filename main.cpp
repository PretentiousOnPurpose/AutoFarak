#include <iostream>
#include "afdtype.hpp"
using namespace std;

int main() {
	double pi = 3.14159;
	double pi_l[] = {1, 2, 3, 4, 5, 6};
	
	auto x1 = afdtype::var(&pi_l[0], 6);
	x1.requiresGrad = true;

	auto x3 = afdtype::pow(x1, 3);
	x3.print();

	
	return 0;
}
