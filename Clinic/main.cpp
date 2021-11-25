#include <thread>
#include <queue>
#include <functional>
#include "clinic.h"

using std::thread;
using std::queue;
using std::bind;

int main() {
	Clinic clinic;
	queue<int> number;

	for (int i = 0; i < 20; i++)
		number.push(i);

	thread* patients = new thread[20];

	while (!number.empty()) {
		int current = number.front();
		number.pop();
		patients[current] = thread(bind(&Clinic::Visit, &clinic, current));
		Delay((rand() % 2 + 1) * 1000);
	}

	for (int i = 0; i < 20; i++)
		patients[i].join();

	delete[] patients;
	patients = NULL;
	system("pause");
	return 0;
}