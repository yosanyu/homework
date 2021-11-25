#include <iostream>
#include <vector>
#include "sort.h"

using namespace std;


string GSortingMethod[] = { "SelectionSort", "BubbleSort", "InsertionSort", "RecursiveMergeSort",
							"IteractiveMergeSort", "RecursiveQuickSort", "IteractiveQuickSort",
							"HeapSort", "builtInSort"};

StackRange::StackRange(int b=0, int e=0) {
	begin = b;
	end = e;
}

string GetSortName(int index) {
	return GSortingMethod[index];
}

void GenerateString(vector<string>& list, int quantity, int size) {
	for (int i = 0; i < quantity; i++) {
		string data = "";
		for (int j = 0; j < size; j++) {
			data += rand() % 26 + 97;
		}
		list.push_back(data);
	}
}

template <class T>
void Copy(vector<T>* lists, vector<T> data, int size) {
	for (int i = 0; i < size; i++)
		lists[i] = data;
}

template <class T>
void Clear(vector<T>* lists, int size) {
	for (int i = 0; i < size; i++)
		lists[i].clear();
}

template <class T>
void DataOuptut(vector<T>& list) {
	for (auto& i : list)
		cout << i << " ";
	cout << "\n";
}

template <class T>
int GetMinIndex(vector<T>& list, int index) {
	int length = list.size();
	int min = index;
	for (int i = index; i < length; i++) {
		if (list[i] < list[min])
			min = i;
	}
	return min;
}

template <class T>
void SelectionSort(vector<T>& list) {
	int length = list.size();
	int min;
	for (int i = 0; i < length;i++) {
		min = GetMinIndex(list, i);
		swap(list[i], list[min]);
	}
}

template <class T>
void BubbleSort(vector<T>& list) {
	int length = list.size();
	for (int i = 0; i < length;i++)
		for (int j = length -1; j > i; j--)
			if (list[j] < list[j-1])
				swap(list[j], list[j-1]);
}

template <class T>
void InsertionSort(vector<T>& list) {
	int length = list.size();
	T insert;
	int j;
	for (int i = 1; i < length; i++) {
		insert = list[i];
		j = i - 1;
		while (j >= 0 && list[j] > insert) {
			list[j+1] = list[j];
			j--;
		}
		list[j+1] = insert;
	}
}

template <class T>
void Merge(vector<T>& list, int front, int mid, int end) {
	vector<T> leftSubList(list.begin() + front, list.begin() + mid + 1);
	vector<T> rightSubList(list.begin() + mid + 1, list.begin() + end + 1);
	int leftIndex = 0;
	int rightIndex = 0;
	int leftSize = leftSubList.size();
	int rightSize = rightSubList.size();
	int index = front;
	
	while (leftIndex < leftSize && rightIndex < rightSize) {
		if (leftSubList[leftIndex] <= rightSubList[rightIndex])
			list[index++] = leftSubList[leftIndex++];
		else
			list[index++] = rightSubList[rightIndex++];
	}
	
	while (leftIndex < leftSize)
		list[index++] = leftSubList[leftIndex++];
	
	while (rightIndex < rightSize)
		list[index++] = rightSubList[rightIndex++];
		
}

template <class T>
void RecursiveMergeSort(vector<T>& list, int front, int end) {
	if (front < end) {
		int mid = front + (end - front) / 2;
		RecursiveMergeSort(list, front, mid);
		RecursiveMergeSort(list, mid + 1, end);
    	Merge(list, front, mid, end);
	}
}

int GetMin(int a, int b) {
	return a < b ? a : b;
}

template <class T>
void swap(vector<T>& a, vector<T>& b) {
	vector<T>& temp = a;
	a = b;
	b = temp;
}

template<class T>
void IteractiveMergeSort(vector<T>& list) {
	int length = list.size();
	vector<string>& original = list;
	vector<string> processed;
	processed.resize(length, "");

	for (int i = 1; i < length; i += i) {
		for (int start = 0; start < length; start += i + i) {
			int front = start;
			int index = start;
			int mid = GetMin(start + i, length);
			int front2 = mid;
			int end = GetMin(start + i * 2, length);

			while (front < mid && front2 < end) {
				if (original[front] < original[front2]) {
					processed[index] = original[front];
					front++;
					index++;
				}
				else
				{
					processed[index] = original[front2];
					front2++;
					index++;
				}
			}

			while (front < mid) {
				processed[index] = original[front];
				front++;
				index++;
			}
			
			while (front2 < end) {
				processed[index++] = original[front2++];
				front2++;
				index++;
			}
		}
		//vector<string>& temp = original;
		//original = processed;
		//processed = temp;
		swap(original, processed);
	}
	if (original != list)
		list = processed;
}

template<class T>
int GetMinIndex(T a, T b, int index1, int index2) {
	return a < b ? index1 : index2;
}

template<class T>
int GetMaxIndex(T a, T b, int index1, int index2) {
	return a > b ? index1 : index2;
}

template<class T>
int GetMedian(vector<T>& list, int a, int b, int c) {
	int temp[2];
	temp[0]	= GetMinIndex(list[a], list[b], a, b);
	temp[1] = GetMinIndex(list[b], list[c], b, c);
	return GetMaxIndex(list[temp[0]], list[temp[1]], temp[0], temp[1]);
}

template<class T>
int Partition(vector<T>& list, int start, int end) {
	int index = start - 1;
	int mid = start + (end - start) / 2;
	int median = GetMedian(list, start, mid, end);
	swap(list[median], list[end]);
	T base = list[end];
	for (int j = start; j < end; j++) {
		if (list[j] <= base)
			swap(list[++index], list[j]);
	}
	swap(list[index+1], list[end]);

	return index + 1;
}

template<class T>
void RecursiveQuickSort(vector<T>& list, int start, int end) {
	if (start < end) {
		int mid = Partition(list, start, end);
		RecursiveQuickSort(list, start, mid - 1);
		RecursiveQuickSort(list, mid + 1, end);
	}
}


template<class T>
void IteractiveQuickSort(vector<T>& list, int length) {
	if (length <= 0)
		return;

	StackRange* range = new StackRange[length];
	int p = 0;

	range[p++] = StackRange(0, length - 1);

	while (p) {
		StackRange temp = range[--p];
		if (temp.begin >= temp.end)
			continue;
		int mid = Partition(list, temp.begin, temp.end);
		range[p++] = StackRange(temp.begin, mid - 1);
		range[p++] = StackRange(mid + 1, temp.end);
	}
	delete [] range;
	range = NULL;
}

template<class T>
void MaxHeapify(vector<T>& list, int start, int end) {
	int dad = start;
	int son = dad * 2 + 1;
	while (son <= end) { 
		if (son + 1 <= end && list[son] < list[son+1])
			son++;
		if (list[dad] > list[son])
			return;
		else { 
			swap(list[dad], list[son]);
			dad = son;
			son = dad * 2 + 1;	
		}
	}
}

template<class T>
void HeapSort(vector<T>& list, int length) {
	/*	let every  node to adjust the array
		have length / 2  node
	 */
	for (int i = length / 2 - 1; i >= 0; i--)
		MaxHeapify(list, i, length - 1);
	
	/*	swap first and last then length - 1
		adjust the array
	*/
	for (int i = length - 1; i > 0; i--) {
		swap(list[0], list[i]);
		MaxHeapify(list, 0, i - 1);
	}
}

// explicit instantiation 
template void Copy(vector<string>* lists, vector<string> data, int size);
template void Clear(vector<string>* lists, int size);
template void DataOuptut(vector<string>& list);
//template int GetMinIndex(vector<string> &list, int index);
template void SelectionSort(vector<string> &list);
template void BubbleSort(vector<string> &list);
template void InsertionSort(vector<string> &list);
template void RecursiveMergeSort(vector<string>& list, int front, int end);
template void IteractiveMergeSort(vector<string>& list);
//template int GetMinIndex(string a, string b, int index1, int index2);
//template int GetMedian(vector<string>& list, int a, int b, int c);
//template int Partition(vector<string>& list, int start, int end);
template void RecursiveQuickSort(vector<string>& list, int start, int end);
template void IteractiveQuickSort(vector<string>& list, int length);
template void MaxHeapify(vector<string>& list, int start, int end);
template void HeapSort(vector<string>& list, int length);





