#include <iostream>
#include "matrix.h"

using namespace std;

Matrix::Matrix(int n) {

	p = new int[n];

	for (int i = 0; i < n; i++)
		p[i] = rand() % 50 + 5;

	pLength = n;

	m = new long long* [n];
	s = new int* [n];
	for (int i = 0; i < n; i++) {
		m[i] = new long long [n];
		s[i] = new int [n];
	}
}

int Matrix::ProductOfIKJ(int i, int j, int k) {
	return p[i - 1] * p[k] * p[j];
}

void Matrix::SetArrayValue(long long q, int i, int j, int k) {
	if (q < m[i][j]) {
		m[i][j] = q;
		s[i][j] = k;
	}
}

long long Matrix::RecursiveMatrixChain(int i, int j) {
	if (i == j) {
		return 0;
	}
	m[i][j] = INT32_MAX;

	for (int k = i; k < j; k++) {
		long long q = RecursiveMatrixChain(i, k) + RecursiveMatrixChain(k + 1, j) + ProductOfIKJ(i, j, k);
		SetArrayValue(q, i, j, k);
	}
	return m[i][j];
}

long long Matrix::LookUpChain(int i, int j) {
	if (m[i][j] < INT32_MAX)
		return m[i][j];

	if (i == j)
		m[i][j] = 0;

	else {
		for (int k = i; k < j; k++) {
			long long q = LookUpChain(i, k) + LookUpChain(k + 1, j) + ProductOfIKJ(i, j, k);
			SetArrayValue(q, i, j, k);
		}
	}

	return m[i][j];

}

void Matrix::MemorizedMatrixChain() {
	for (int i = 1; i < pLength; i++)
		for (int j = 1; j < pLength; j++)
			m[i][j] = INT32_MAX;

	long long temp = LookUpChain(1, pLength - 1);
}


void Matrix::MatrixChainOrder() {
	for (int i = 0; i < pLength; i++)
		m[i][i] = 0;
	
	for (int len = 2; len < pLength; len++) {
		for (int i = 1; i < pLength - len + 1; i++) {
			int j = i + len - 1;
			m[i][j] = INT32_MAX;
			for (int k = i; k < j; k++) {
				long long q = m[i][k] + m[k + 1][j] + ProductOfIKJ(i, j, k);
				SetArrayValue(q, i, j, k);
			}
		}
	}
	
}

void Matrix::PrintOptimatPattern(int i, int j) {
	if (i == j)
		cout << "A" << i;
	else {
		cout << "(";
		PrintOptimatPattern(i, s[i][j]);
		PrintOptimatPattern(s[i][j] + 1, j);
		cout << ")";
	}
}

void Matrix::Clear() {
	for (int i = 0; i < pLength; i++) {
		for (int j = 0; j < pLength; j++) {
			m[i][j] = 0;
			s[i][j] = 0;
		}
	}
}

