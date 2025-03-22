#include <iostream>
using namespace std;

template <typename T, typename Func>
afdtype afdtype::applyElementWiseMathOp(const afdtype * val, const T & op2, Func operation) {
	double ** data = (double **)calloc(val->dims[0], sizeof(double));
	for (int i = 0; i < val->dims[0]; i++) {
		data[i] = new double[val->dims[1]]();
	}

	if constexpr (is_arithmetic<T>::value) {		
		for (int i = 0; i < val->dims[0]; i++) {
			for (int j = 0; j < val->dims[1]; j++) {
				data[i][j] = operation(val->data[i][j], op2);
			}
		}
	} else if (is_same<T, afdtype>::value) {
		for (int i = 0; i < val->dims[0]; i++) {
			for (int j = 0; j < val->dims[1]; j++) {
				data[i][j] = operation(val->data[i][j], op2.data[i][j]);
			}
		}
	} else {
		cout << "Invalid data type" << endl;
	}

	return afdtype::var(data, val->dims[0], val->dims[1]);	
}

template <typename T>
afdtype afdtype::pow(const afdtype & val, const T & op2) {
	return applyElementWiseMathOp(&val, op2, [](double a, double b) { return std::pow(a, b); });
}

template <typename T>
afdtype afdtype::operator+(const T & op2) const {
	return applyElementWiseMathOp(this, op2, [](double a, double b) { return a + b; });
}


template <typename T>
afdtype afdtype::operator-(const T & op2) const {
	return applyElementWiseMathOp(this, op2, [](double a, double b) { return a - b; });
}


template <typename T>
afdtype afdtype::operator*(const T & op2) const {
	return applyElementWiseMathOp(this, op2, [](double a, double b) { return a * b; });
}


template <typename T>
afdtype afdtype::operator/(const T & op2) const {
	return applyElementWiseMathOp(this, op2, [](double a, double b) { return a / b; });
}
