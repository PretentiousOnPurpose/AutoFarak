#ifndef AFDTYPE_H
#define AFDTYPE_H

#include <iostream>

class afdtype {
public:
	// Metadata
	int numDims;
	int * dims;
	bool requiresGrad;

	// Data
	double ** data;

	//Constructors and Methods
	afdtype(int numDims, int * dims, bool requiresGrad);
	~afdtype();

	afdtype var(double val);
	afdtype var(double * vec, int dim);
	afdtype var(double ** mat, int dim1, int dim2);
	afdtype zeros_like(int dim1, int dim2);

	afdtype var(double val, bool requiresGrad);
	afdtype var(double * vec, int dim, bool requiresGrad);
	afdtype var(double ** mat, int dim1, int dim2, bool requiresGrad);
	afdtype zeros_like(int dim1, int dim2, bool requiresGrad);

	void print();

	
};

#endif
