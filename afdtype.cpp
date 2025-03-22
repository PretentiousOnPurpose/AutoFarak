
#include <iostream>
#include "afdtype.hpp"
#include <cmath>
using namespace std;

void afdtype::print() {
	if (numDims == 0) {
		cout << data[0][0] << endl;
	} else if (numDims == 1) {
		for (int i = 0; i < dims[1]; i++) {
			cout << data[0][i] << " ";
		}
		cout << endl;
	} else {

		for (int i = 0; i < dims[0]; i++) {
			for (int j = 0; j < dims[1]; j++) {
				cout << data[i][j] << " ";
			}
			cout << endl;
		}
		cout << endl;
	}

	cout << "Requires Grad: " << this->requiresGrad << endl;
}

afdtype::afdtype(int numDims, int * dims, bool requiresGrad = false) {
	this->numDims = numDims;
	this->dims = dims;
	this->requiresGrad = requiresGrad;

	if (numDims == 0) {
		data = (double **)calloc(1, sizeof(double));
		data[0] = (double *)calloc(1, sizeof(double));
	} else if (numDims == 1) {
		data = (double **)calloc(1, sizeof(double));
	}
}

afdtype afdtype::var(double val, bool requiresGrad = false) {
	int * dims = (int *)calloc(2, sizeof(int));
	dims[0] = 1;
	dims[1] = 1;

	afdtype d_var(0, dims, requiresGrad);

	d_var.data[0][0] = val;

	return d_var;
}

afdtype afdtype::var(double * val, int dim, bool requiresGrad = false) {
	int * dims = (int *)calloc(2, sizeof(int));
	dims[0] = 1;
	dims[1] = dim;

	afdtype d_var(1, dims, requiresGrad);

	d_var.data[0] = val;

	return d_var;
}

afdtype afdtype::var(double ** val, int dim1, int dim2, bool requiresGrad = false) {
	int * dims = (int *)calloc(2, sizeof(int));
	dims[0] = dim1;
	dims[1] = dim2;

	afdtype d_var(2, dims, requiresGrad);

	d_var.data = val;
	
	return d_var;
}

afdtype afdtype::zeros_like(int dim1, int dim2, bool requiresGrad = false) {
	int * dims = (int *)calloc(2, sizeof(int));
	int numDims = -1;

	if (dim1 + dim2 == 2) {
		numDims = 0;
	} else if ((dim1 == 1) || (dim2 == 1)) {
		numDims = 1;
	} else {
		numDims = 2;
	}

	afdtype d_var(numDims, dims, requiresGrad);

	d_var.data = (double **)calloc(dim1, sizeof(double));
	
	for (int i = 0; i < dim1; i++) {
		d_var.data[i] = (double *)calloc(dim2, sizeof(double));
	}

	return d_var;
}

template <typename T>
afdtype afdtype::operator+(const T & op2) {
	double ** data = (double **)calloc(this->dims[0], sizeof(double));
	bool all_good = false;


	if ((is_arithemtic<T>::value) || ((this->dims[0] == op2.dims[0]) && (this->dims[1] == op2.dims[1]))) {
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
afdtype afdtype::operator-(const T & op2) {
	double ** data = (double **)calloc(this->dims[0], sizeof(double));
	bool all_good = false;


	if ((is_arithemtic<T>::value) || ((this->dims[0] == op2.dims[0]) && (this->dims[1] == op2.dims[1]))) {
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
afdtype afdtype::operator*(const T & op2) {
	double ** data = (double **)calloc(this->dims[0], sizeof(double));
	bool all_good = false;


	if ((is_arithemtic<T>::value) || ((this->dims[0] == op2.dims[0]) && (this->dims[1] == op2.dims[1]))) {
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
afdtype afdtype::operator/(const T & op2) {
	double ** data = (double **)calloc(this->dims[0], sizeof(double));
	bool all_good = false;


	if ((is_arithemtic<T>::value) || ((this->dims[0] == op2.dims[0]) && (this->dims[1] == op2.dims[1]))) {
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

afdtype afdtype::sin(afdtype val) {
	afdtype res = afdtype::zeros_like(val);

	for (int i = 0; i < val.dims[0]; i++) {
		for (int j = 0; j < val.dims[1]; j++) {
			res.data[i][j] = math::sin(val.data[i][j]);
		}
	}

	return res;
}

afdtype afdtype::cos(afdtype val) {
	afdtype res = afdtype::zeros_like(val);

	for (int i = 0; i < val.dims[0]; i++) {
		for (int j = 0; j < val.dims[1]; j++) {
			res.data[i][j] = math::cos(val.data[i][j]);
		}
	}

	return res;
}

template <typename T>
afdtype afdtype::pow(afdtype val1, T val2) {
	afdtype res = afdtype::zeros_like(val1);

	for (int i = 0; i < val1.dims[0]; i++) {
		for (int j = 0; j < val1.dims[1]; j++) {
			if (is_arithmetic<T>::value) {
				res.data[i][j] = math::pow(val1.data[i][j], val2);
			} else if ((val1.dims[0] == val2.dims[0]) && (val1.dims[1] == val2.dims[1])) {
				res.data[i][j] = math::power(val1.data[i][j], val2.data[i][j]);
			} else if (val2.numDims == 0) {
				res.data[i][j] = math::pow(val1[i][j], val2[0][0])
			}
		}
	}

	return res;
}

afdtype::~afdtype() {
//	for (int j = 0; j < dims[1]; j++) {
//		free(data[j]);
//	}

//	free(data);

	data = nullptr;
}
