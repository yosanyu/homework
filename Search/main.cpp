#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <map>
#include <unordered_map>
#include "search.h"

using namespace std;

void Search();

template<class T>
void BinarySearch(T* data, T* test, int dataSize, int testSize);

template<class T>
void BSTSearch(T* data, T* test, int dataSize, int testSize);

template<class T>
void HTSearch(T* data, T*test, int dataSize, int testSize);

template<class T>
void MapSearch(T* data, T* test, int dataSize, int testSize);

template<class T>
void UNMapSearch(T* data, T* test, int dataSize, int testSize);


template void BinarySearch(string* data, string* test, int dataSize, int testSize);
template void BSTSearch(string* data, string* test, int dataSize, int testSize);
template void HTSearch(string* data, string* test, int dataSize, int testSize);
template void MapSearch(string* data, string* test, int dataSize, int testSize);
template void UNMapSearch(string* data, string* test, int dataSize, int testSize);


int main() {

	srand(unsigned(time(NULL)));

	for(int i=0;i<5;i++)
		Search();

	system("pause");
	return 0;
}

void Search() {

	int dataSize = 10000000;
	int testSize = 10000000;

	string* data = new string[dataSize];
	GenerateString(data, dataSize);

	string* test = new string[testSize];
	GenerateString(test, testSize);

	BinarySearch(data, test, dataSize, testSize);
	BSTSearch(data, test, dataSize, testSize);
	HTSearch(data, test, dataSize, testSize);
	MapSearch(data, test, dataSize, testSize);
	UNMapSearch(data, test, dataSize, testSize);

	delete [] data;
	data = NULL;

	delete [] test;
	test = NULL;

}

template<class T>
void BinarySearch(T* data, T* test, int dataSize, int testSize) {
	T* copyData = new T[dataSize];
	int count = 0;
	CopyData(data, copyData, dataSize);
	int sortStart = clock();
	sort(copyData, copyData + dataSize);
	int sortEnd = clock();
	int start = clock();
	for (int i = 0; i < testSize; i++) {
		bool check = BinarySearch(copyData, dataSize, test[i]);
		if (check)
			count++;
	}
	int end = clock();
	cout << "iteration Binary Search find " << count << " times\n";
	cout << "create cost = " << sortEnd - sortStart << "ms\n";
	cout << "find = " << end - start << "ms\n";
	cout << "total = " << end - start + sortEnd - sortStart << "ms\n\n";

	count = 0;
	start = clock();
	for (int i = 0; i < testSize; i++) {
		bool check = BinarySearch(copyData, 0, dataSize -1, test[i]);
		if (check)
			count++;
	}
	end = clock();
	cout << "recursive Binary Search find " << count << " times\n";
	cout << "create cost = " << sortEnd - sortStart << "ms\n";
	cout << "find = " << end - start << "ms\n";
	cout << "total = " << end - start + sortEnd - sortStart << "ms\n\n";

	delete [] copyData;
	copyData = NULL;
}

template<class T>
void BSTSearch(T* data, T* test, int dataSize, int testSize) {
	BSTNode<string>* root = NULL;
	int count = 0;
	int start1 = clock();
	root = CreateBST(root, data, dataSize);
	int end1 = clock();
	int start2 = clock();
	//root->PreOrder(root);
	for (int i = 0; i < testSize; i++) {
		bool check = root->Search(root, test[i]);
		if (check)
			count++;
	}
	int end2 = clock();
	cout << "Binary Search Tree find " << count << " times\n";
	cout << "create cost = " << end1 - start1 << "ms\n";
	cout << "find = " << end2 - start2 << "ms\n";
	cout << "total = " << end2 - start2 + end1 - start1 << "ms\n\n";

	delete root;
	root = NULL;
}

template<class T>
void HTSearch(T* data, T* test, int dataSize, int testSize) {
	int HTlength = int(dataSize * 2);
	int count = 0;
	HTChain<T>* HT = new HTChain<T>[HTlength];
	int start1 = clock();
	CreateHT(HT, data, dataSize, HTlength);
	int end1 = clock();
	int start2 = clock();
	for (int i = 0; i < testSize; i++) {
		int hashnum = FindHashNum(test[i], HTlength);
		bool check = HT[hashnum].IsInChain(test[i]);
		if (check)
			count++;
	}
	int end2 = clock();
	//for (int i = 0; i < HTlength; i++)
	//	HT[i].OutputChain();
	cout << "Hash Table find " << count << " times\n";
	cout << "create cost = " << end1 - start1 << "ms\n";
	cout << "find = " << end2 - start2 << "ms\n";
	cout << "total = " << end2 - start2 + end1 - start1 << "ms\n\n";
	delete [] HT;
	HT = NULL;
}

template<class T>
void MapSearch(T* data, T* test, int dataSize, int testSize) {
	map<T, int> RBT;
	typename map<T, int>::iterator iter;
	int count = 0;
	int start1 = clock();
	CreateMap(RBT, data, dataSize);
	int end1 = clock();
	int start2 = clock();
	for (int i = 0; i < testSize; i++) {
		iter = RBT.find(test[i]);
		if (iter != RBT.end())
			count++;
	}
	int end2 = clock();
	RBT.clear();
	cout << "map find " << count << " times\n";
	cout << "create cost = " << end1 - start1 << "ms\n";
	cout << "find = " << end2 - start2 << "ms\n";
	cout << "total = " << end2 - start2 + end1 - start1 << "ms\n\n";
}

template<class T>
void UNMapSearch(T* data, T* test, int dataSize, int testSize) {
	unordered_map<T, int> HT;
	typename unordered_map<T, int>::iterator iter;
	int count = 0;
	int start1 = clock();
	CreateUNMap(HT, data, dataSize);
	int end1 = clock();
	int start2 = clock();
	for (int i = 0; i < testSize; i++) {
		iter = HT.find(test[i]);
		if (iter != HT.end())
			count++;
	}
	int end2 = clock();
	HT.clear();
	cout << "unordered_map find " << count << " times\n";
	cout << "create cost = " << end1 - start1 << "ms\n";
	cout << "find = " << end2 - start2 << "ms\n";
	cout << "total = " << end2 - start2 + end1 - start1 << "ms\n\n";
}