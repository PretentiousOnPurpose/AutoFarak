#include <iostream>
using namespace std;

template <typename T>
afdtype afdtype::pow(const afdtype & val, const T & op2) {
double ** data = (double **)calloc(val.dims[0], sizeof(double));
	for (int i = 0; i < val.dims[0]; i++) {
		data[i] = new double[val.dims[1]]();
	}

	if constexpr (is_arithmetic<T>::value) {		
		for (int i = 0; i < val.dims[0]; i++) {
			for (int j = 0; j < val.dims[1]; j++) {
				data[i][j] = std::pow(val.data[i][j], op2);
			}
		}
	} else if (is_same<T, afdtype>::value) {
		for (int i = 0; i < val.dims[0]; i++) {
			for (int j = 0; j < val.dims[1]; j++) {
				data[i][j] = std::pow(val.data[i][j], op2.data[i][j]);
			}
		}
	} else {
		cout << "Invalid data type" << endl;
	}


	return afdtype::var(data, val.dims[0], val.dims[1]);	
}

template <typename T>
afdtype afdtype::operator+(const T & op2) const {
	double ** data = (double **)calloc(this->dims[0], sizeof(double));
	for (int i = 0; i < this->dims[0]; i++) {
		data[i] = new double[this->dims[1]]();
	}

	if constexpr (is_arithmetic<T>::value) {		
		for (int i = 0; i < this->dims[0]; i++) {
			for (int j = 0; j < this->dims[1]; j++) {
				data[i][j] = this->data[i][j] + op2;
			}
		}
	} else if (is_same<T, afdtype>::value) {
		for (int i = 0; i < this->dims[0]; i++) {
			for (int j = 0; j < this->dims[1]; j++) {
				data[i][j] = this->data[i][j] + op2.data[i][j];
			}
		}
	} else {
		cout << "Invalid data type" << endl;
	}


	return afdtype::var(data, this->dims[0], this->dims[1]);
}

template <typename T>
afdtype afdtype::operator-(const T & op2) const {
	double ** data = (double **)calloc(this->dims[0], sizeof(double));
	for (int i = 0; i < this->dims[0]; i++) {
		data[i] = new double[this->dims[1]]();
	}

	if constexpr (is_arithmetic<T>::value) {		
		for (int i = 0; i < this->dims[0]; i++) {
			for (int j = 0; j < this->dims[1]; j++) {
				data[i][j] = this->data[i][j] - op2;
			}
		}
	} else if (is_same<T, afdtype>::value) {
		for (int i = 0; i < this->dims[0]; i++) {
			for (int j = 0; j < this->dims[1]; j++) {
				data[i][j] = this->data[i][j] - op2.data[i][j];
			}
		}
	} else {
		cout << "Invalid data type" << endl;
	}


	return afdtype::var(data, this->dims[0], this->dims[1]);
}

template <typename T>
afdtype afdtype::operator*(const T & op2) const {
	double ** data = (double **)calloc(this->dims[0], sizeof(double));
	for (int i = 0; i < this->dims[0]; i++) {
		data[i] = new double[this->dims[1]]();
	}

	if constexpr (is_arithmetic<T>::value) {		
		for (int i = 0; i < this->dims[0]; i++) {
			for (int j = 0; j < this->dims[1]; j++) {
				data[i][j] = this->data[i][j] * op2;
			}
		}
	} else if (is_same<T, afdtype>::value) {
		for (int i = 0; i < this->dims[0]; i++) {
			for (int j = 0; j < this->dims[1]; j++) {
				data[i][j] = this->data[i][j] * op2.data[i][j];
			}
		}
	} else {
		cout << "Invalid data type" << endl;
		exit(1);
	}


	return afdtype::var(data, this->dims[0], this->dims[1]);
}

template <typename T>
afdtype afdtype::operator/(const T & op2) const {
	double ** data = (double **)calloc(this->dims[0], sizeof(double));
	for (int i = 0; i < this->dims[0]; i++) {
		data[i] = new double[this->dims[1]]();
	}

	if constexpr (is_arithmetic<T>::value) {	
		if (op2 == 0) {
			cout << "Division by zero not allowed" << endl;
			exit(1);
		}	

		for (int i = 0; i < this->dims[0]; i++) {
			for (int j = 0; j < this->dims[1]; j++) {
				data[i][j] = this->data[i][j] / op2;
			}
		}
	} else if (is_same<T, afdtype>::value) {
		for (int i = 0; i < this->dims[0]; i++) {
			for (int j = 0; j < this->dims[1]; j++) {
				if (op2.data[i][j] == 0) {
					cout << "Division by zero not allowed" << endl;
					exit(1);
				}	

				data[i][j] = this->data[i][j] / op2.data[i][j];
			}
		}
	} else {
		cout << "Invalid data type" << endl;
	}


	return afdtype::var(data, this->dims[0], this->dims[1]);
}

