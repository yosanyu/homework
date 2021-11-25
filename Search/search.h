#pragma once
#ifndef _SEARCH_H_
#define _SEARCH_H_

#include <string>
#include <map>
#include <unordered_map>

using namespace std;

extern const int GStringSize;

void GenerateString(string* list, int quantity);

template<class T>
void CopyData(T* data, T* copyData,int dataSize);

// Binary Search Tree
template<class T>
class BSTNode {
public:
	BSTNode(); // constructor
	BSTNode* GetNode(T data);
	BSTNode* Insert(BSTNode* root,T data);
	bool Search(BSTNode* root, T key);
	void Visit(BSTNode* root);
	void PreOrder(BSTNode* root);
	//~BSTNode();
private:
	T data;
	BSTNode* left;
	BSTNode* right;
};

// Hash Table
template<class T>
class HTNode {
public:
	HTNode();
	T data;
	HTNode* next;
};

template<class T>
class HTChain {
public:
	HTChain();
	//~HTChain();
	HTChain& Insert(const T& data);
	bool IsInChain(T key);
	void OutputChain();
private:
	HTNode<T>* first;
};

// iteration
template<class T>
bool BinarySearch(T* list, int length, T key);

// recursive
template<class T>
bool BinarySearch(T* list, int low, int up, T key);

template<class T>
BSTNode<T>* CreateBST(BSTNode<T>* root, T* data, int dataSize);

template<class T>
void CreateHT(HTChain<T>* HashTable, T* data, int dataSize, int HTSize);

// hash function
template<class T>
int FindHashNum(T key, int HTSize);

int FindHashNum(string key, int HTSize);

template<class T>
void CreateMap(map<T, int>& RBT, T* data, int dataSize);

template<class T>
void CreateUNMap(unordered_map<T, int>& HT, T* data, int dataSize);

#endif // !_SEARCH_H_

