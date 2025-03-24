#ifndef AFDTYPE_H
#define AFDTYPE_H

#include <iostream>
#include <vector>
#include <functional>
using namespace std;

class afdtype {
public:
	// Metadata
	int numDims;
	int * dims;
	bool requiresGrad;
	int typeVar; // 0 - constant, 1 - variable

	vector<afdtype> b_deps;
	afdtype * grad;

	// Data
	double ** data;

	// Forward and Backward Fns
//	afdtype (*fwdFn)(const afdtype... args);
//	afdtype (*bwdFn)(const afdtype... args);
	std::function<afdtype(const afdtype &)> bwdFn_1;
	std::function<afdtype(const afdtype &, const afdtype &)> bwdFn_2;

	//Constructors and Methods
	afdtype(int numDims, int * dims, bool typeVar, bool requiresGrad);
	afdtype();
	~afdtype();

	static afdtype var(double val, bool typeVar = true, bool requiresGrad = false);
	static afdtype var(double * vec, int dim, bool typeVar = true, bool requiresGrad = false);
	static afdtype var(double ** mat, int dim1, int dim2, bool typeVar = true, bool requiresGrad = false);
	static afdtype zeros(int dim1, int dim2, bool typeVar = true, bool requiresGrad = false);
	static afdtype zeros_like(const afdtype & val);
	static afdtype sin(const afdtype &);
	static afdtype sin_bwd(const afdtype &);
	static afdtype cos(const afdtype &);
	static afdtype cos_bwd(const afdtype &);

	template <typename T>
	static afdtype pow(const afdtype &, const T &);

	static afdtype pow_bwd(const afdtype &, const afdtype &);

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

	double * operator[](const int idx) const;
	double * operator[](int idx);

	void print();

	
};

#include "afdtype.tpp"

#endif
