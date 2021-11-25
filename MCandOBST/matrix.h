#pragma once

class Matrix {
public:
	Matrix(int n);
	int ProductOfIKJ(int i, int j, int k);
	void SetArrayValue(long long q, int i, int j, int k); // m[i][j] and s[i][j]
	long long RecursiveMatrixChain(int i, int j);
	long long LookUpChain(int i, int j);
	void MemorizedMatrixChain();
	void MatrixChainOrder();
	void PrintOptimatPattern(int i, int j);
	void Clear();
private:
	int* p;
	int pLength;
	long long ** m;
	int ** s;
};


