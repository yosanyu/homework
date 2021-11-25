#include<iostream>
#include<ctime>
#include<cstdlib>
#include"Maze.h"
#include"Stack.h"

using namespace std;

void Set_move();
void Copmare(Maze *A, int K);

int main() {
	
	srand(time(0));
	Set_move();
	
	int K;
	cout << "Input the Maze which do you want to create\n";
	cout << "K = ";
	cin >> K;
	
	int N;
	cout << "\nInput the Maze's Size\n";
	cout << "N = ";
	cin >> N;
	
	int P;
	cout << "\nInput the Probability\n";
	cout << "P = ";
	cin >> P;
	
	Maze *A = new Maze[K];
	
	for(int i=0;i<K;i++)	
		A[i] = Maze(N+2, P);
				
	Copmare(A, K);
	
	delete [] A;
	A = NULL;
	
	return 0;
}

void Copmare(Maze *A, int K) {
	
	int Find_one = 0;
	bool check;

	for(int i=0;i<K;i++) {
	//	A -> output();
		check = A -> path(1);
		if(check)
			Find_one++;
	//	A -> output();
		A -> setMark();	
	A++;
			
}	
	for(int i=0;i<K;i++)
		A--;
		
	int Find_two = 0;
	
	for(int i=0;i<K;i++) {
	//	A -> output();
		check = A -> path(2);
		if(check)
			Find_two++;
	//	A -> output();	
	A -> erase();
	A++;
}

	cout << "\n First way = " << Find_one << "\n"; 
	cout << "\nSecond way = " << Find_two << "\n";
	
	
}

