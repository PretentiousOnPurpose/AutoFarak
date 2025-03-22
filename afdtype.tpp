#include <iostream>
using namespace std;


template <typename Func>
afdtype afdtype::applyElementWiseMathOneOp(const afdtype * val, Func operation) {
	afdtype res = afdtype::zeros_like(*val);

	for (int i = 0; i < val->dims[0]; i++) {
		for (int j = 0; j < val->dims[1]; j++) {
			res.data[i][j] = operation(val->data[i][j]);
		}
	}

	return res;
}

template <typename T, typename Func>
afdtype afdtype::applyElementWiseMathTwoOps(const afdtype * val, const T & op2, Func operation) {
	afdtype res = afdtype::zeros_like(*val);
	
	if constexpr (is_arithmetic<T>::value) {		
		for (int i = 0; i < val->dims[0]; i++) {
			for (int j = 0; j < val->dims[1]; j++) {
				res.data[i][j] = operation(val->data[i][j], op2);
			}
		}
	} else if (is_same<T, afdtype>::value) {
		for (int i = 0; i < val->dims[0]; i++) {
			for (int j = 0; j < val->dims[1]; j++) {
				res.data[i][j] = operation(val->data[i][j], op2.data[i][j]);
			}
		}
	} else {
		cout << "Invalid data type" << endl;
	}

	return res;	
}

template <typename T>
afdtype afdtype::pow(const afdtype & val, const T & op2) {
	return applyElementWiseMathTwoOps(&val, op2, [](double a, double b) { return std::pow(a, b); });
}

template <typename T>
afdtype afdtype::operator+(const T & op2) const {
	return applyElementWiseMathTwoOps(this, op2, [](double a, double b) { return a + b; });
}


template <typename T>
afdtype afdtype::operator-(const T & op2) const {
	return applyElementWiseMathTwoOps(this, op2, [](double a, double b) { return a - b; });
}


template <typename T>
afdtype afdtype::operator*(const T & op2) const {
	return applyElementWiseMathTwoOps(this, op2, [](double a, double b) { return a * b; });
}


template <typename T>
afdtype afdtype::operator/(const T & op2) const {
	return applyElementWiseMathTwoOps(this, op2, [](double a, double b) { return a / b; });
}
