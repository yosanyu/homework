#include<iostream>
#include<cstdlib>
#include"Maze.h"
#include"Stack.h"

using namespace std;

struct Offsets {
	int a; // row
	int b; // column
} move[8];

Maze::Maze() {
	
	N = 0;
	P = 0;
	maze = NULL;
	mark = NULL;
	
}

Maze::Maze(int n, int p) {
	
	N = n;
	P = p;
	int a;
	
	maze = new int*[n];
	for(int i=0; i<n; i++)
    	maze[i] = new int[n];
    	
	mark = new int*[n];
	for(int i=0; i<n; i++)
    	mark[i] = new int[n];
    	
    for(int i=0;i<n;i++) {
    	
    	for(int j=0;j<n;j++) {
    		
    		mark[i][j] = 0;
    		
    		if(i == 0 || i == n - 1)
    			maze[i][j] = 1;
    			
    		else if (j == 0 || j == n - 1)
    			maze[i][j] = 1;
    		
    		else {
    			
    			a = rand() % 100;
    			
    			if(a < P)
    				maze[i][j] = 0;
    			
    			else
    				maze[i][j] = 1;
    			
			}
    		
		}
    	
    	
	}
//	cout << "n = " << n << " P = " << P << "\n"; 
}

/*Maze::~Maze() {
	
	cout << "call destructor\n";
	
	for(int i=0; i<N; i++) {
		
    	delete [] maze [i]; 
    	delete [] mark [i];
    }
	delete [] maze;
	delete [] mark;
}*/

void Maze::erase() {
//	cout << "call destructor\n";
	
	for(int i=0; i<N; i++) {
		
    	delete [] maze [i]; 
    	delete [] mark [i];
    }
	delete [] maze;
	delete [] mark;
}

void Maze::output() {
	
//	cout << "n = " << N << "\n";
//	cout << "P = " << P << "\n";
	
	cout << "----maze----\n";
	for(int i=0;i<N;i++) {
		
		for(int j=0;j<N;j++)
			cout << maze[i][j];
		cout << "\n";
		
	}
	
	cout << "\n mark = \n";
	for(int i=0;i<N;i++) {
		
		for(int j=0;j<N;j++)
			cout << mark[i][j];
		cout << "\n";
		
	}
	
}

void Maze::setMark() {
	
	for(int i=0;i<N;i++) 
		for(int j=0;j<N;j++)
			mark[i][j] = 0;

}

bool Maze::path(int way) {
	
	int count = 0;
	
	if(maze[1][1] == 1 || maze[N-2][N-2]) {
		//	cout << "No path in maze\n";
			return 0;
		}
		
	Stack S;
	Item temp;
	
	mark[1][1] = 1; //start at (1,1)
	temp.x = 1 ; temp.y = 1 ; temp.dir = 2; // E  
    S.Push(temp) ;
	
	while(!S.IsEmpty()) {
		
		temp = S.Top();
    	S.Pop(); // unstack
		 
    	int i = temp.x;
		int j = temp.y; 
		int d = temp.dir;
        int h = j + move[d].b; 
        
        while(d < 8) {  // move forward
			int g = i + move[d].a; 
        	int h = j + move[d].b; 
        	
        	if ((g == N-2) && (h == N-2)) {    //reached  exit  and output path 
        		
        		mark[i][j] = 1;
        		
        	/*	cout << "----path----\n";
				S.Reverse();
				S.Output();      	 	
            	cout << "(" << i << "," << j << ")\n"; 
            	cout << "(" << g << "," << h << ")\n"; 
            
            	cout << "path found\n";
            	S.erase();*/
            //	S.Output();
            	return 1;
        
	}
			if ((!maze[g][h]) && (!mark[g][h])) {        // new position 
			
               	mark[g][h] = 1 ;
               
			//   	cout << "mark(" << g << "," << h << ")\n"; 
               	temp.x = i; 
				temp.y = j;
				temp.dir = d + way;
				 
               	S.Push(temp);                // stack it 
               	i = g;
				j = h;
				d = 0; // N              // move to (g, h) 
               	
               } 
               
                else
					d += way; // try next direction 
        } 
	}
}


void Set_move() {
	
	move[0].a = -1 ; move[0].b = 0; 
	move[1].a = -1 ; move[1].b = 1; 
	move[2].a = 0 ; move[2].b = 1; 
	move[3].a = 1 ; move[3].b = 1; 
	move[4].a = 1 ; move[4].b = 0; 
	move[5].a = 1 ; move[5].b = -1; 
	move[6].a = 0 ; move[6].b = -1; 
	move[7].a = -1 ; move[7].b = -1; 
	
}
