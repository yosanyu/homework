#include<iostream>
#include<string>
#include"mipstomc.h"
#include"function.h"

using namespace std;

int main() {
	char choice;
	bool bRunning = true;
	while (bRunning) {
		Start();
		cout << "\n\nDo you want to input again?\n";
		cout << "(y/n) Your choice is  ";
		cin >> choice;
		cin.get();
		if (choice == 'y' || choice == 'Y')
			system("cls");
		else
			bRunning = false;
	}
	system("pause");
	return 0;
}