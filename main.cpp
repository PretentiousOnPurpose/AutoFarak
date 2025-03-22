#include <iostream>
#include "afdtype.hpp"
using namespace std;

int main() {
	double x_d[] = {10.0, 20.0, 30.0};
	afdtype x1 = afdtype::var(&x_d[0], 3);

	double x_d2[] = {10.0, 20.0, 30.0};
	afdtype x2 = afdtype::var(&x_d2[0], 3);

	x1.print();
	x2.print();

	auto x3 = x1 - x2;
	auto x4 = x1 * x2;
	auto x5 = x1 / x2;

	x3.print();
	x4.print();
	x5.print();

	return 0;
}
