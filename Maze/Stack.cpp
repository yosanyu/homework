#include<iostream>
#include"Stack.h"

using namespace std;

Stack_Node::Stack_Node() {
	
	x = 0;
	y = 0;
	dir = 0;
	Next = NULL;
	
}

Stack_Node::Stack_Node(Item content) {
	
	x = content.x;
	y = content.y;
	dir = content.dir;
	Next = NULL;
	
}

Stack::Stack() {
	
	size = 0;
	top = NULL;
	
}

/*Stack::~Stack() {
	
	Stack_Node *current;
	while( top != NULL) {
		
		current = top;
		top = top -> Next;
		delete current;
		
	}
	
}*/


int Stack::getSize() {
	
	return size;
	
}

bool Stack::IsEmpty() {
	
	return (size == 0);
	
}

Item Stack::Top() {
	
	Item current;
	
	if( IsEmpty() ) {
		
		cout << "The Stack is empty\n";
		current.x = 0;
		current.y = 0;
		current.dir = 0;
		return current;
		
	}
	
	current.x = top -> x;
	current.y = top -> y;
	current.dir = top -> dir;
		
	return current;
	
//	cout << "(" << top -> x << "," << top -> y << ")\n";
	
}

void Stack::erase() {
	
	Stack_Node *current;
	
	while( top  != NULL) {
		
		current = top;
		top = top -> Next;
		delete current;
		
	}
	
}

void Stack::Push(Item content) {
	
	if ( IsEmpty() ) {
 		
        top = new Stack_Node(content);
        size++;
        return;
        
    }
    
	Stack_Node *NewNode = new Stack_Node(content);  // Push the data that it is in the top
    NewNode -> Next = top;                    
    top = NewNode;
    size++;
	
}

void Stack::Pop() {
	
	if( IsEmpty() ) {
		
		cout << "The Stack is empty\n";
		return;
		
	}
	
	Stack_Node *Delete = top;
	top = top -> Next;
    delete Delete;
    Delete = NULL;
    size--;
	
}

void Stack::Output() {
		
	while(top != NULL) {
		
		cout << "(" << top -> x << "," << top -> y << ")\n";
		top = top -> Next;
	
	}
	
}

void Stack::Reverse() {
	
	if (top == NULL || top -> Next == NULL) {
        // list is empty or list has only one node
        return;
    }

    Stack_Node *previous = NULL;
    Stack_Node *current = top;
    Stack_Node *preceding = top -> Next;

    while (preceding != NULL) {
        current -> Next = previous;      
        previous = current;            
        current = preceding;           
        preceding = preceding -> Next;   
    }                                  

    current -> Next = previous;        
    top = current;           
}
