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
//	list<afdtype> comp_graph;

	// Data
	double ** data;

	//Constructors and Methods
	afdtype(int numDims, int * dims, bool requiresGrad);
	~afdtype();

	static afdtype var(double val, bool requiresGrad = false);
	static afdtype var(double * vec, int dim, bool requiresGrad = false);
	static afdtype var(double ** mat, int dim1, int dim2, bool requiresGrad = false);
	static afdtype zeros(int dim1, int dim2, bool requiresGrad = false);
	static afdtype zeros_like(const afdtype & val, bool requiresGrad = false);

	template <typename T>
	afdtype operator+(const T &) const;

	template <typename T>
	afdtype operator-(const T &) const;

	template <typename T>
	afdtype operator*(const T &) const;

	template <typename T>
	afdtype operator/(const T &) const;

	afdtype sin(afdtype);
	afdtype cos(afdtype);
	
	template <typename T>
	afdtype pow(afdtype, T);

	void print();

	
};

#include "afdtype.tpp"

#endif
