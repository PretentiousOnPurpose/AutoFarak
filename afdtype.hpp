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
	static afdtype sin(const afdtype &);
	static afdtype cos(const afdtype &);
	
	template <typename T>
	static afdtype pow(const afdtype &, const T &);

	template <typename T, typename Func>
	static afdtype applyElementWiseMathTwoOps(const afdtype *, const T &, Func operation);
	
	template <typename Func>
	static afdtype applyElementWiseMathOneOp(const afdtype *, Func operation);
		
	template <typename T>
	afdtype operator+(const T &) const;

	template <typename T>
	afdtype operator-(const T &) const;

	template <typename T>
	afdtype operator*(const T &) const;

	template <typename T>
	afdtype operator/(const T &) const;

	const double * operator[](int idx) const;
	double * operator[](int idx);

	void print();

	
};

#include "afdtype.tpp"

#endif
