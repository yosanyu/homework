#pragma once

// Optimal Binary Search Tree
class OBST {
public:
	OBST(int n);
	void Initilize(int n);
	void SetPQ(int n);
	void OptimalBST(int n);
	void Print(int n);
private:
	double* p;
	double* q;
	double** e;
	double** w;
	int** root;
};
