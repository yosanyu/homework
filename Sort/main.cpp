#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <fstream>
#include "sort.h"

using namespace std;

// string's size
const int GStringSize = 6;

void Run();

int main() {

	srand((unsigned)time(NULL));
	Run();

	return 0;
}

void Run() {
	ofstream result;
	result.open("result.txt");
	result << "Testing...\n\n";

	/*
	compute the time that sort costed
	data quantity
	*/

	int totalTime[9] = {};
	int testData[] = { 20, 40, 60, 80, 100, 120, 2000000, 4000000, 6000000, 8000000, 10000000};
	int vectorSize;
	int times;
	int way;
	int index;

	vector<string> data;

	for (int i = 0; i < sizeof(testData) / sizeof(int); i++) {
		vector<string>* test;

		for (int j = 0; j < 10; j++)
			totalTime[i] = 0;

		if (i < 6) {
			vectorSize = 5000;
			times = 1000;
		}
		else {
			vectorSize = 1;
			times = 1000;
		}

		test = new vector<string>[vectorSize];

		for (int k = 0; k < times; k++) {

			data.clear();
			GenerateString(data, testData[i], GStringSize);

			if (i < 6) {
				way = 0;
				index = 0;
			}
			else {
				way = 3;
				index = 3;
			}

			int start;
			int end;

			if (i < 6) {
				Copy(test, data, vectorSize);

				start = clock();
				for (int l = 0; l < vectorSize; l++)
					SelectionSort(test[l]);
				end = clock();
				totalTime[way] += (end - start);
				way++;

				Clear(test, vectorSize);
				Copy(test, data, vectorSize);

				start = clock();
				for (int l = 0; l < vectorSize; l++)
					BubbleSort(test[l]);
				end = clock();
				totalTime[way] += (end - start);
				way++;

				Clear(test, vectorSize);
				Copy(test, data, vectorSize);

				start = clock();
				for (int l = 0; l < vectorSize; l++)
					InsertionSort(test[l]);
				end = clock();
				totalTime[way] += (end - start);
				way++;

				Clear(test, vectorSize);
			}

			Copy(test, data, vectorSize);

			start = clock();
			for (int l = 0; l < vectorSize; l++)
				RecursiveMergeSort(test[l], 0, test[l].size() - 1);
			end = clock();
			totalTime[way] += (end - start);
			way++;

			Clear(test, vectorSize);
			Copy(test, data, vectorSize);

			start = clock();
			for (int l = 0; l < vectorSize; l++)
				IteractiveMergeSort(test[l]);
			end = clock();
			totalTime[way] += (end - start);
			way++;

			Clear(test, vectorSize);
			Copy(test, data, vectorSize);

			start = clock();
			for (int l = 0; l < vectorSize; l++)
				RecursiveQuickSort(test[l], 0, test[l].size() - 1);
			end = clock();
			totalTime[way] += (end - start);
			way++;

			Clear(test, vectorSize);
			Copy(test, data, vectorSize);

			start = clock();
			for (int l = 0; l < vectorSize; l++)
				IteractiveQuickSort(test[l], test[l].size());
			end = clock();
			totalTime[way] += (end - start);
			way++;

			Clear(test, vectorSize);
			Copy(test, data, vectorSize);

			start = clock();
			for (int l = 0; l < vectorSize; l++)
				HeapSort(test[l], test[l].size());
			end = clock();
			totalTime[way] += (end - start);
			way++;

			Clear(test, vectorSize);
			Copy(test, data, vectorSize);

			start = clock();
			for (int l = 0; l < vectorSize; l++)
				sort(test[l].begin(), test[l].end());
			end = clock();
			totalTime[way] += (end - start);
			way++;

			Clear(test, vectorSize);

		}

		result << "test data = " << testData[i] << "\n";
		result << "vectorSize = " << vectorSize << "\n";
		result << "times = " << times << "\n\n";

		for (int j = 0; j < way - index; j++) {
			result << j + 1 << ". " << GetSortName(j + index) << "\n";
			result << "use  " << totalTime[j + index] << "ms\n\n";
		}

		cout << "i = " << i + 1 << "\n";

		delete[] test;
		test = NULL;

	}

	result << "\n\nending";

	result.close();
}
