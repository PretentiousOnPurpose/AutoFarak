#ifndef AFDTYPE_H
#define AFDTYPE_H

#include <iostream>
#include <list>

class afdtype {
public:
	// Metadata
	int numDims;
	int * dims;
	bool requiresGrad;

	// global metadata
	list<afdtype> comp_graph;

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

	afdtype operator+(const afdtype &);
	afdtype operator-(const afdtype &);
	afdtype operator*(const afdtype &);
	afdtype operator/(const afdtype &);

	void print();

	
};

#endif
