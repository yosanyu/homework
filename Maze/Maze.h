#ifndef Maze_H
#define Maze_H

#include<iostream>

using namespace std;

class Maze {
public:
	Maze();
	Maze(int n, int p);
//	~Maze();
	void erase();
	void output();
	void setMark();
	bool path(int way);
private:
	int N;
	int P;
	int **maze;
	int **mark;
};

#endif
