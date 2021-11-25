#ifndef _SORT_H_
#define _SORT_H_

#include <vector>
#include <string>

using namespace std;

extern string GSortingMethod[];

struct StackRange {
	int begin;
	int end;
	StackRange(int b, int e);
};

string GetSortName(int index);

void GenerateString(vector<string>& list, int quantity, int size);

template <class T>
void Copy(vector<T>* lists, vector<T> data, int size);

template <class T>
void Clear(vector<T>* lists, int size);

template <class T>
void DataOuptut(vector<T>& list);

template <class T>
int GetMinIndex(vector<T>& list, int index);

template <class T>
void SelectionSort(vector<T>& list);

template <class T>
void BubbleSort(vector<T>& list);

template <class T>
void InsertionSort(vector<T>& list);

template <class T>
void Merge(vector<T>& list, int front, int mid, int end);

template <class T>
void RecursiveMergeSort(vector<T>& list, int front, int end);

int GetMin(int a, int b);

template <class T>
void swap(vector<T>& a, vector<T>& b);

template<class T>
void IteractiveMergeSort(vector<T> &list);

template<class T>
int GetMinIndex(T a, T b, int index1, int index2);

template<class T>
int GetMaxIndex(T a, T b, int index1, int index2);

template<class T>
int GetMedian(vector<T>& list, int a, int b, int c);

template<class T>
int Partition(vector<T>& list, int begin, int end);

template<class T>
void RecursiveQuickSort(vector<T>& list, int start, int end);

template<class T>
void IteractiveQuickSort(vector<T>& list, int length);

template<class T>
void MaxHeapify(vector<T>& list, int start, int end);

template<class T>
void HeapSort(vector<T>& list, int length);

#endif