#include <iostream>
#include <string>
#include <cstdlib>
#include <string>
#include <map>
#include <unordered_map>
#include "search.h"

using namespace std;

// string's length
const int GStringSize = 6;

void GenerateString(string* list, int quantity) {
	for (int i = 0; i < quantity; i++) {
		string temp = "";
		for (int j = 0; j < GStringSize; j++)
			temp += rand() % 26 + 97;
		list[i] = temp;
	}
}

template<class T>
void CopyData(T* data, T* copyData, int dataSize) {
	for (int i = 0; i < dataSize; i++)
		copyData[i] = data[i];
}

template<class T>
bool BinarySearch(T* list, int length, T key) {
	int low = 0;
	int up = length - 1;
	int mid;
	while (low <= up) {
		// avoid overflow
		mid = low + (up - low) / 2;

		if (key == list[mid])
			return true;
		else if (key > list[mid])
			low = mid + 1;
		// if(key < A[mid])
		else 
			up = mid - 1;

	}
	// can't find
	return false; 
}

template<class T>
bool BinarySearch(T* list, int low, int up, T key) {
	if (low <= up) {

		int mid = low + (up - low) / 2;

		if (key == list[mid])
			return true;
		else if (key > list[mid])
			return BinarySearch(list, mid + 1, up, key);
		else
			return BinarySearch(list, low, mid - 1, key);

	}
	return false;
}

template<class T>
BSTNode<T>::BSTNode() {
	data = NULL;
	left = NULL;
	right = NULL;
}

BSTNode<string>::BSTNode() {
	data.clear();
	left = NULL; 
	right = NULL;
}
template<class T>
BSTNode<T>* BSTNode<T>::GetNode(T data) {
	BSTNode* newNode = new BSTNode();
	newNode->data = data;
	return newNode;
}

template<class T>
BSTNode<T>* BSTNode<T>::Insert(BSTNode* root, T data) {
	if (root == NULL)
		root = GetNode(data);
	else if (data < root->data)
		root->left = Insert(root->left, data);
	else if (data > root->data)
		root->right = Insert(root->right, data);

	return root;
}

template<class T>
bool BSTNode<T>::Search(BSTNode* root, T key) {
	if (root == NULL)
		return false;
	else if (key == root->data)
		return true;
	else if (key < root->data)
		return Search(root->left, key);
	else // if(key > root -> data)
		return Search(root->right, key);
}

template<class T>
void BSTNode<T>::PreOrder(BSTNode* root) {
	if (root != NULL) {
		Visit(root);
		PreOrder(root->left);
		PreOrder(root->right);
	}
}

template<class T>
void BSTNode<T>::Visit(BSTNode* root) {
	cout << root->data << " ";
}

template<class T>
HTNode<T>::HTNode() {
	data = NULL;
	next = NULL;
}

HTNode<string>::HTNode() {
	data.clear();
	next = NULL;
}

template<class T>
HTChain<T>::HTChain() {
	first = new HTNode<T>;
	first->data.clear();
	first->next = NULL;
}

template<class T>
HTChain<T>& HTChain<T>::Insert(const T& data) {
	HTNode<T>* insertedNode = new HTNode<T>;

	insertedNode->data = data;
	insertedNode->next = first;
	first = insertedNode;

	return *this;
}

template<class T>
bool HTChain<T>::IsInChain(T key) { // linear search 
	HTNode<T>* temp = first;
	while (temp) {
		if (key == temp->data)
			return true;
		else 
			temp = temp->next;
	}
	return false;
}

template<class T>
void HTChain<T>::OutputChain() {
	HTNode<T>* temp = first;
	while (temp) {
		cout << temp->data << " ";
		temp = temp->next;
	}
	cout << "\n";
}

template<class T>
BSTNode<T>* CreateBST(BSTNode<T>* root, T* data, int dataSize) {
	root = root->Insert(root, data[0]);
	for (int i = 1; i < dataSize; i++)
		root->Insert(root, data[i]);
	return root;
}

template<class T>
void CreateHT(HTChain<T>* HashTable, T* data, int dataSize, int HTSize) {

	for (int i = 0; i < dataSize; i++) {
		int hash = 0;
		hash = FindHashNum(data[i], HTSize);
		bool check = HashTable[hash].IsInChain(data[i]);
		if (!check) // check is false
			HashTable[hash].Insert(data[i]);
	}

}

int FindHashNum(string key, int HTSize) {
	unsigned int hashNum = 0;
	unsigned int highorder;
	for (int i = 0; i < GStringSize; i++) {
		highorder = hashNum & 0xF8000000;
		hashNum = hashNum << 5;
		hashNum = hashNum ^ (highorder >> 27);
		hashNum = hashNum ^ key[i];
	}
	return hashNum % HTSize;
}

template<class T>
int FindHashNum(T key, int HTSize) {
	string temp = to_string(key);
	unsigned int hashNum = 0;
	unsigned int highorder;

	for (int i = 0; i < temp.size(); i++) {
		highorder = hashNum & 0xF8000000;
		hashNum = hashNum << 5;
		hashNum = hashNum ^ (highorder >> 27);
		hashNum = hashNum ^ temp[i];
	}
	return hashNum % HTSize;
}

template<class T>
void CreateMap(map<T, int>& RBT, T* data, int dataSize) {
	for (int i = 0; i < dataSize; i++)
		RBT.insert(pair<T, int>(data[i], i+1));
}

template<class T>
void CreateUNMap(unordered_map<T, int>& HT, T* data, int dataSize) {
	for (int i = 0; i < dataSize; i++)
		HT.insert(pair<T, int>(data[i], i+1));
}



template BSTNode<string>* BSTNode<string>::Insert(BSTNode* root, string test);
template bool BSTNode<string>::Search(BSTNode* root, string key);
template void BSTNode<string>::PreOrder(BSTNode* root);
template HTChain<string>::HTChain();
template bool HTChain<string>::IsInChain(string key);
template void HTChain<string>::OutputChain();
template void CopyData(string* data, string* copyData, int dataSize);
template bool BinarySearch(string* list, int length, string key);
template bool BinarySearch(string* list, int low, int up, string key);
template BSTNode<string>* CreateBST(BSTNode<string>* root, string* data, int dataSize);
template void CreateHT(HTChain<string>* HashTable, string* data, int dataSize, int HTSize);
template void CreateMap(map<string, int>& RBT, string* data, int dataSize);
template void CreateUNMap(unordered_map<string, int>& HT, string* data, int dataSize);

