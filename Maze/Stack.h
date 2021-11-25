#ifndef Stack_H
#define Stack_H

#include<iostream>

using namespace std;

struct Item {
	int x;
    int y;
    int dir;
};

class Stack_Node {
public:
	Stack_Node();
	Stack_Node(Item content);
	int x;
	int y;
	int dir;
	Stack_Node *Next;
};

class Stack {
public:
	Stack();
//	~Stack();
    int getSize();
    Item Top();
	bool IsEmpty();
	void erase();
	void Push(Item content);
    void Pop();
    void Output();
    void Reverse();
private:
	Stack_Node *top;
	int size;
};

#endif
