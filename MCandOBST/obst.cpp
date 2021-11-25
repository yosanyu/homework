#include <iostream>
#include <cstdlib>
#include <iomanip>
#include "obst.h"

using namespace std;

constexpr double GWeights = 0.001;
constexpr int GTimes = 1000;

OBST::OBST(int n) {

	p = new double[n + 1];
	q = new double[n + 1];
	e = new double* [n + 2];
	w = new double* [n + 2];
	root = new int* [n + 1];

	for (int i = 0; i < n + 2; i++) {
		if (i < n + 1)
			root[i] = new int [n + 1];
		e[i] = new double [n + 1];
		w[i] = new double [n + 1];
	}

	SetPQ(n);

}

void OBST::Initilize(int n) {

	for (int i = 0; i < n + 2; i++) {
		for (int j = 0; j < n + 1; j++) {
			e[i][j] = 0.0;
			w[i][j] = 0.0;
		}
	}
	for (int i = 0; i < n + 1; i++)
		for (int j = 0; j < n + 1; j++)
			root[i][j] = 0;
}

void OBST::SetPQ(int n) {

	for (int i = 0; i < n + 1; i++) {
		if (i > 0)
			p[i] = GWeights;
		q[i] = GWeights;
	}

	for (int i = 0; i < GTimes - n * 2 - 1; i++) {
		bool choice = rand() % 2;
		switch (choice) {
			case 0:
				p[rand() % n + 1] += GWeights;
				break;
			default:
				q[rand() % (n + 1)] += GWeights;
				break;
		}
	}
}

void OBST::OptimalBST(int n) {

	for (int i = 1; i < n + 2; i++) {
		e[i][i - 1] = q[i - 1];
		w[i][i - 1] = q[i - 1];
	}

	for (int len = 1; len < n + 1; len++) {
		for (int i = 1; i < n - len + 2; i++) {
			int j = i + len - 1;
			e[i][j] = INT32_MAX;
			w[i][j] = w[i][j - 1] + p[j] + q[j];
			for (int r = i; r < j + 1; r++) {
				double t = e[i][r - 1] + e[r + 1][j] + w[i][j];
				if (t < (e[i][j])) {
					e[i][j] = t;
					root[i][j] = r;
				}
			}
		}
	}
}

void OBST::Print(int n) {

	cout << fixed << setprecision(2);

	cout << "e \n";
	for (int i = 0; i < n + 2; i++) {
		for (int j = 0; j < n + 1; j++)
			cout << e[i][j] << " ";
		cout << "\n";
	}

	cout << "\n\nw\n";

	for (int i = 0; i < n + 2; i++) {
		for (int j = 0; j < n + 1; j++)
			cout << w[i][j] << " ";
		cout << "\n";
	}

	cout << "\n\nr\n";

	for (int i = 0; i < n + 1; i++) {
		for (int j = 0; j < n + 1; j++)
			cout << root[i][j] << " ";
		cout << "\n";
	}
}
