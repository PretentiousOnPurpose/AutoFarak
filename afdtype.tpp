#include <iostream>
using namespace std;

template <typename T>
afdtype afdtype::operator+(const T & op2) const {
	double ** data = (double **)calloc(this->dims[0], sizeof(double));
	bool all_good ;


	if ((is_arithmetic<T>::value) || ((this->dims[0] == op2.dims[0]) && (this->dims[1] == op2.dims[1]))) {
		all_good = true;
	} else {
		cout << "Incompatible dimensions" << endl;
		exit(1);
	}

	if (all_good) {
		for (int i = 0; i < this->dims[0]; i++) {
			data[i] = (double *)calloc(this->dims[1], sizeof(double));

			for (int j = 0; j < this->dims[1]; j++) {
				if (is_arithmetic<T>::value) {
					data[i][j] = this->data[i][j] + op2;
				} else {
					data[i][j] = this->data[i][j] + op2.data[i][j];
				}
			}
		}
	}

	return afdtype::var(data, this->dims[0], this->dims[1]);
}

template <typename T>
afdtype afdtype::operator-(const T & op2) const {
	double ** data = (double **)calloc(this->dims[0], sizeof(double));
	bool all_good ;


	if ((is_arithmetic<T>::value) || ((this->dims[0] == op2.dims[0]) && (this->dims[1] == op2.dims[1]))) {
		all_good = true;
	} else {
		cout << "Incompatible dimensions" << endl;
		exit(1);
	}

	if (all_good) {
		for (int i = 0; i < this->dims[0]; i++) {
			data[i] = (double *)calloc(this->dims[1], sizeof(double));

			for (int j = 0; j < this->dims[1]; j++) {
				if (is_arithmetic<T>::value) {
					data[i][j] = this->data[i][j] - op2;
				} else {
					data[i][j] = this->data[i][j] - op2.data[i][j];
				}
			}
		}
	}

	return afdtype::var(data, this->dims[0], this->dims[1]);
}

template <typename T>
afdtype afdtype::operator*(const T & op2) const {
	double ** data = (double **)calloc(this->dims[0], sizeof(double));
	bool all_good ;


	if ((is_arithmetic<T>::value) || ((this->dims[0] == op2.dims[0]) && (this->dims[1] == op2.dims[1]))) {
		all_good = true;
	} else {
		cout << "Incompatible dimensions" << endl;
		exit(1);
	}

	if (all_good) {
		for (int i = 0; i < this->dims[0]; i++) {
			data[i] = (double *)calloc(this->dims[1], sizeof(double));

			for (int j = 0; j < this->dims[1]; j++) {
				if (is_arithmetic<T>::value) {
					data[i][j] = this->data[i][j] * op2;
				} else {
					data[i][j] = this->data[i][j] * op2.data[i][j];
				}
			}
		}
	}

	return afdtype::var(data, this->dims[0], this->dims[1]);
}

template <typename T>
afdtype afdtype::operator/(const T & op2) const {
	double ** data = (double **)calloc(this->dims[0], sizeof(double));
	bool all_good ;


	if ((is_arithmetic<T>::value) || ((this->dims[0] == op2.dims[0]) && (this->dims[1] == op2.dims[1]))) {
		all_good = true;
	} else {
		cout << "Incompatible dimensions" << endl;
		exit(1);
	}

	if (all_good) {
		for (int i = 0; i < this->dims[0]; i++) {
			data[i] = (double *)calloc(this->dims[1], sizeof(double));

			for (int j = 0; j < this->dims[1]; j++) {
				if (is_arithmetic<T>::value) {
					data[i][j] = this->data[i][j] / op2;
				} else {
					data[i][j] = this->data[i][j] / op2.data[i][j];
				}
			}
		}
	}

	return afdtype::var(data, this->dims[0], this->dims[1]);
}

template <typename T>
afdtype afdtype::pow(afdtype val1, T val2) {
	afdtype res = afdtype::zeros_like(val1);

	for (int i = 0; i < val1.dims[0]; i++) {
		for (int j = 0; j < val1.dims[1]; j++) {
			if (is_arithmetic<T>::value) {
				res.data[i][j] = std::pow(val1.data[i][j], val2);
			} else if ((val1.dims[0] == val2.dims[0]) && (val1.dims[1] == val2.dims[1])) {
				res.data[i][j] = power(val1.data[i][j], val2.data[i][j]);
			} else if (val2.numDims == 0) {
				res.data[i][j] = pow(val1.data[i][j], val2[0][0]);
			} else {
				cout << "Incompatible dimensions" << endl;
				exit(1);
			}
		}
	}

	return res;
}
