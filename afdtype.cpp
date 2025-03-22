
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

const double * afdtype::operator[](int idx) const {
	return this->data[idx];
}

double * afdtype::operator[](int idx) {
	return this->data[idx];
}

afdtype::afdtype(int numDims, int * dims, bool requiresGrad ) {
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

afdtype afdtype::var(double val, bool requiresGrad ) {
	int * dims = (int *)calloc(2, sizeof(int));
	dims[0] = 1;
	dims[1] = 1;

	afdtype d_var(0, dims, requiresGrad);

	d_var.data[0][0] = val;

	return d_var;
}

afdtype afdtype::var(double * val, int dim, bool requiresGrad ) {
	int * dims = (int *)calloc(2, sizeof(int));
	dims[0] = 1;
	dims[1] = dim;

	afdtype d_var(1, dims, requiresGrad);

	d_var.data[0] = val;

	return d_var;
}

afdtype afdtype::var(double ** val, int dim1, int dim2, bool requiresGrad ) {
	int * dims = (int *)calloc(2, sizeof(int));
	dims[0] = dim1;
	dims[1] = dim2;

	afdtype d_var(2, dims, requiresGrad);

	d_var.data = val;
	
	return d_var;
}

afdtype afdtype::zeros(int dim1, int dim2, bool requiresGrad ) {
	int * dims = (int *)calloc(2, sizeof(int));
	int numDims = -1;

	dims[0] = dim1;
	dims[1] = dim2;

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

afdtype afdtype::zeros_like(const afdtype & val, bool requiresGrad) {
	return afdtype::zeros(val.dims[0], val.dims[1], requiresGrad);
}

afdtype afdtype::sin(const afdtype & val) {
	return afdtype::applyElementWiseMathOneOp(&val, [](double a) { return std::sin(a); });
}

afdtype afdtype::cos(const afdtype & val) {
	return afdtype::applyElementWiseMathOneOp(&val, [](double a) { return std::cos(a); });
}


afdtype::~afdtype() {
//	for (int j = 0; j < dims[1]; j++) {
//		free(data[j]);
//	}

//	free(data);

	data = nullptr;
}
