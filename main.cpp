#include <iostream>
#include "afdtype.hpp"
using namespace std;

int main() {
	double pi = 3.14159;
	double pi_l[] = {0, pi / 2, pi /4, pi};
	
	auto x1 = afdtype::var(&pi_l[0], 4);
	auto x2 = afdtype::var(&pi_l[0], 4);

	auto x3 = afdtype::sin(x1);

	x3.print();

	
	return 0;
}
