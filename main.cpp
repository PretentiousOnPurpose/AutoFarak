#include <iostream>
#include "afdtype.hpp"
using namespace std;

int main() {
	afdtype x_1(10.0);
	
	double x_d[] = {10.0, 20.0, 30.0};

	afdtype x(&x_d[0], 3);

	x_1.print();
	x.print();

	return 0;
}
