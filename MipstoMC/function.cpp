#include<iostream>
#include<string>
#include<vector>
#include<thread>
#include"mipstomc.h"
#include"function.h"

using namespace std;

void Start() {
	vector<int> branch;
	vector<int> getLabel;
	vector<string> instruction;

	Input(instruction);
	unsigned instructionsNumber = instruction.size();
	MipsToMC* mipsToMC = new MipsToMC[instructionsNumber];
	thread* threads = new thread[instructionsNumber];

	for (unsigned i = 0; i < instructionsNumber; i++) {
		mipsToMC[i].SetInstruction(instruction[i]);
		// Use thread to process string 
		threads[i] = thread(&MipsToMC::InstructionProcess, &mipsToMC[i]);
	}

	EndThread(threads, instructionsNumber);

	for (unsigned i = 0; i < instructionsNumber; i++) {
		if (mipsToMC[i].GetOrder() == "beq" || mipsToMC[i].GetOrder() == "bne")
			branch.push_back(i);
		else if (mipsToMC[i].GetLabel() != "")
			getLabel.push_back(i);
	}

	for (unsigned i = 0; i < instructionsNumber; i++) {
		mipsToMC[i].CheckType();
		// Use thread to choice type.
		threads[i] = thread(&MipsToMC::ChoiceType, &mipsToMC[i]);
	}

	EndThread(threads, instructionsNumber);
	
	// Find label position.
	for (unsigned i = 0;i < branch.size();i++) {
		int current = branch[i];
		bool bHaveAddress = false;
		for (unsigned j = 0;j < getLabel.size();j++) {
			int current2 = getLabel[j];
			if (mipsToMC[current].GetLabel() == mipsToMC[current2].GetLabel()) {
				mipsToMC[current].SetAddress(4 * (current2 - current - 1));
				bHaveAddress = true;
			}
		}
		if(!bHaveAddress)
			mipsToMC[current].SetErrorType();
	}
	for (unsigned i = 0;i < instructionsNumber;i++) {
		mipsToMC[i].SetMachineCode();
		cout << mipsToMC[i];
	}

	delete [] mipsToMC;
	mipsToMC = NULL;
	delete[] threads;
	threads = NULL;
	branch.clear();
	getLabel.clear();
	instruction.clear();
}

void Input(vector<string>& instruction) {
	string temp;
	while (getline(cin, temp), temp.length() != 0) {
		instruction.push_back(temp);
	}
}

void EndThread(thread* threads, const int size) {
	// Wait thread end.
	for (int i = 0; i < size; i++)
		threads[i].join();
}

int StringToInt(string &convert) {
	vector<int> temp;
	int address = 0;
	for (unsigned i = 0; i < convert.length(); i++)
		temp.push_back(convert[i] - '0');
	reverse(temp.begin(), temp.end());
	for (unsigned i = 0; i < temp.size(); i++) {
		address += (temp[i] * Power(10, i));
	}
	return address;
}

int Power(const int x, const int pow) {
	int temp = 1;
	for (int i = 0; i < pow; i++)
		temp *= x;
	return temp;
}

string DemcialToBinary(int convert, const int& bits) {
	string binaryCode = "";
	string temp = "";
	while (convert > 0) {
		temp += (convert % 2 + 48);
		convert /= 2;
	}
	// fill zero
	for (unsigned i = 0; i < bits - temp.length(); i++)
		binaryCode += '0';

	reverse(temp.begin(), temp.end());

	for (unsigned i = 0; i < temp.length(); i++)
		binaryCode += temp[i];

	return binaryCode;
}

string OutputMC(string& machineCode) {
	string temp = "";
	for (unsigned i = 0; i < machineCode.length(); i++) {
		temp += machineCode[i];
		// Every four numbers give one space.
		if ((i + 1)% 4 == 0)
			temp += " ";
	}
	return temp;
}
bool IsAddress(string& address) {
	bool bIsAddress = true;
	// We know address consists of numbers.
	// So if we find a letters in address.
	// We can confirm it is not an address.
	for (unsigned i = 0; i < address.length(); i++) {
		bool bCheckUpper = (address[i] >= 'A' && address[i] <= 'Z');
		bool bCheckLower = (address[i] >= 'a' && address[i] <= 'z');
		if (bCheckUpper || bCheckLower) {
			bIsAddress = false;
			break;
		}
	}
	return bIsAddress;
}