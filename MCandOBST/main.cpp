#include <iostream>
#include <cstdlib>
#include <ctime>
#include "matrix.h"
#include "obst.h"

using namespace std;

int main() {
	
	srand(unsigned(time(NULL)));
	int n = 10;

	for (int j = 0; j < 5; j++) {

		cout << "RecursiveMatrixChain\n";
		Matrix a(n);
		int start = clock();
		for (int i = 0; i < 100000; i++) {
			a.RecursiveMatrixChain(1, 9);
			if (i < 100000 - 1)
				a.Clear();
		}
		int end = clock();
		a.PrintOptimatPattern(1, n - 1);
		a.Clear();
		cout << "\n" << end - start << "\n";
		cout << "\n\n";
		cout << "MemorizedMatrixChain\n";
		start = clock();
		for (int i = 0; i < 100000; i++) {
			a.MemorizedMatrixChain();
			if (i < 100000 - 1)
				a.Clear();
		}
		end = clock();
		a.PrintOptimatPattern(1, n - 1);
		a.Clear();
		cout << "\n" << end - start << "\n";
		cout << "\n\n";
		cout << "MatrixChainOrder\n";
		start = clock();
		for (int i = 0; i < 100000; i++) {
			a.MatrixChainOrder();
			if (i < 100000 - 1)
				a.Clear();
		}
		end = clock();
		a.PrintOptimatPattern(1, n - 1);
		cout << "\n" << end - start << "\n";
		cout << "\n\n";

	}
	
	int start = clock();
	for (int i = 0; i < 100; i++) {
		OBST a(10);
		a.OptimalBST(10);
		//a.Print(10);
	}
	int end = clock();
	cout << end - start << "\n";
	return 0;
}