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

	static afdtype var(double val);
	static afdtype var(double * vec, int dim);
	static afdtype var(double ** mat, int dim1, int dim2);
	static afdtype zeros_like(int dim1, int dim2);

	static afdtype var(double val, bool requiresGrad);
	static afdtype var(double * vec, int dim, bool requiresGrad);
	static afdtype var(double ** mat, int dim1, int dim2, bool requiresGrad);
	static afdtype zeros_like(int dim1, int dim2, bool requiresGrad);

	void print();

	
};

#endif
