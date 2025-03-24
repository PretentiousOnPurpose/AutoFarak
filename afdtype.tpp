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

	res.b_deps.push_back(*val);

	return res;
}

template <typename T, typename Func>
afdtype afdtype::applyElementWiseMathTwoOps(const afdtype * val, const T & op2, Func operation) {
	afdtype res = afdtype::zeros_like(*val);	
	afdtype op2_n;

	if constexpr (is_arithmetic<T>::value) {		
		op2_n = afdtype::var(op2);
	} else {
		op2_n = op2;
	}
	
	for (int i = 0; i < val->dims[0]; i++) {	
		for (int j = 0; j < val->dims[1]; j++) {
			if (op2_n.numDims == 0) {
				res.data[i][j] = operation(val->data[i][j], op2_n.data[0][0]);
			} else {
				res.data[i][j] = operation(val->data[i][j], op2_n.data[i][j]);
			}
		}
	}

	res.b_deps.push_back(*val);
	res.b_deps.push_back(op2_n);
		
	return res;	
}

template <typename T>
afdtype afdtype::pow(const afdtype & val, const T & op2) {
	afdtype op2_n;

	if constexpr (is_arithmetic<T>::value) {		
		op2_n = afdtype::var(op2);
	} else {
		op2_n = op2;
	}
	
	afdtype res = applyElementWiseMathTwoOps(&val, op2_n, [](double a, double b) { return std::pow(a, b); });

	res.grad = (afdtype *)calloc(1, sizeof(afdtype));
	*(res.grad) = afdtype::pow_bwd(val, op2_n);

	return res;

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

