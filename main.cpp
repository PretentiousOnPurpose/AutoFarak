#include <iostream>
#include "afdtype.hpp"
using namespace std;

int main() {
	afdtype x = afdtype::var(10.0, true);

	double x_d[] = {10.0, 20.0, 30.0};

	afdtype x1 = afdtype::var(&x_d[0], 3);


	x1.print();
	x.print();

	return 0;
}
