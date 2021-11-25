#include<iostream>
#include<string>
#include<vector>
#include"mipstomc.h"
#include"function.h"

using namespace std;

// declare global variable

string gInstructions[] = {"add", "sub", "lw", "sw", "beq", "bne"};
int gInstructionsNumber[] = { 0, 0, 35, 43, 4, 5};
string gRegisters[] = {"t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7", "t8",
					   "t9", "s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7" };
int gRegisterNumbers[] = { 8, 9, 10, 11, 12, 13, 14, 15, 24, 25, 16, 17, 18, 19, 20, 21, 22, 23};

// get array's size

int gInstructionsLenght = sizeof(gInstructionsNumber) / sizeof(int);
int gRegisterLenght = sizeof(gRegisterNumbers) / sizeof(int);

// initialization

RegisterValue::RegisterValue(){
	number = 0;
	name = "";
}

MipsToMC::MipsToMC() {
	decimalCode.op = -1;
	decimalCode.rs = -1;
	decimalCode.rt = -1;
	decimalCode.rd = -1;
	decimalCode.shamt = -1;
	decimalCode.funct = -1;
	decimalCode.address = -1;
	binaryCode.op = "";
	binaryCode.rs = "";
	binaryCode.rt = "";
	binaryCode.rd = "";
	binaryCode.shamt = "";
	binaryCode.funct = "";
	binaryCode.address = "";
	inputInstruction = "";
	afterProcessInstruction = "";
	order = "";
	machineCode = "";
	label = "";
	instructionIndex = -1;
	opType = ' ';
}

// process string

void MipsToMC::InstructionProcess() {
	string temp = "";
	int index = 0;
	FindLabel();

	for (int i = 0; i < gInstructionsLenght; i++) {
		// find instruction
		if (afterProcessInstruction.find(gInstructions[i]) != afterProcessInstruction.npos) {
			order = gInstructions[i];
			instructionIndex = i;
			index = afterProcessInstruction.find(gInstructions[i]);
		}
	}
	// remove content before instruction
	for (unsigned i = index; i < afterProcessInstruction.length(); i++)
			temp += afterProcessInstruction[i];
	afterProcessInstruction = temp;
}

void MipsToMC::FindLabel() {
	// check label
	if (inputInstruction.find(":") != inputInstruction.npos) {
		int index = inputInstruction.find(":");
		string temp = "";
		for (int i = 0; i < index; i++)
			temp += inputInstruction[i];
		label = temp;
	}
	afterProcessInstruction = inputInstruction;
}

void MipsToMC::CheckType() {
	// check and set opType
	if(instructionIndex == -1)
		SetErrorType();
	else if (instructionIndex < 2)
		opType = 'r';
	else
		opType = 'i';
}

void MipsToMC::ChoiceType() {
	if (opType == 'r')
		RType();
	if (opType == 'i')
		IType();
}

void MipsToMC::RType() {
	RegisterValue* registers = new RegisterValue[3];
	string temp = afterProcessInstruction;
	string temp2 = "";
	temp.replace(0, order.length(), "");

	for (unsigned i = 0; i < temp.length(); i++) {
		if (temp[i] != ' ' && temp[i] != ',' && temp[i] != '$')
			temp2 += temp[i];
	}


	// three regs, their lenght is 6
	if (temp2.length() != 6) {
		SetErrorType();
	}

	else {
		// get reg data
		int regCount = 0;
		for (int i = 0; i < 3; i++) {
			registers[i].name = temp2.substr(i * 2, 2);
			for (int j = 0; j < gRegisterLenght; j++) {
				if (registers[i].name == gRegisters[j]) {
					registers[i].number = gRegisterNumbers[j];
					regCount++;
					break;
				}
			}
		}
		// // We konw that rtype has three regs.
		if (regCount != 3)
			SetErrorType();
		else {
			decimalCode.rd = registers[0].number;
			decimalCode.rs = registers[1].number;
			decimalCode.rt = registers[2].number;
		}

	}
	delete[] registers;
	registers = NULL;
}

void MipsToMC::IType() {
	RegisterValue* registers = new RegisterValue[2];
	string temp = afterProcessInstruction;
	string temp2 = "";
	string address = "";
	temp.replace(0, order.length(), "");

	for (unsigned i = 0; i < temp.length(); i++) {
		if (temp[i] != ' ' && temp[i] != ',' && temp[i] != '$' && temp[i] != '(' && temp[i] != ')')
			temp2 += temp[i];
	}

	if (temp2.length() < 5)
		SetErrorType();
	else {
		if (order == "lw" || order == "sw") {
			registers[0].name = temp2.substr(0, 2);
			registers[1].name = temp2.substr(temp2.length() - 2, 2);
			for (unsigned i = 2; i < temp2.length() - 2; i++)
				address += temp2[i];
			if (IsAddress(address))
				SetAddress(address);
			else
				SetErrorType();
		}
		else {
			registers[0].name = temp2.substr(0, 2);
			registers[1].name = temp2.substr(2, 2);
			label = temp2.substr(4, temp2.length());
		}
		int regCount = 0;
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < gRegisterLenght; j++)
				if (registers[i].name == gRegisters[j]) {
					registers[i].number = gRegisterNumbers[j];
					regCount++;
					break;
				}
		}
		// We konw that itype has two regs.
		if(regCount != 2)
			SetErrorType();
		else {
			if (order == "lw" || order == "sw") {
				decimalCode.rs = registers[1].number;
				decimalCode.rt = registers[0].number;
			}

			else {
				decimalCode.rs = registers[0].number;
				decimalCode.rt = registers[1].number;
			}
		}
	}
	delete[] registers;
	registers = NULL;
}

void MipsToMC::SetOpCode() {
	decimalCode.op = gInstructionsNumber[instructionIndex];
}

void MipsToMC::SetAddress(string address) {
	decimalCode.address = StringToInt(address);
}

void MipsToMC::SetMachineCode() {
	if (opType == 'r') {
		SetOpCode();
		SetShamtCode();
		SetFunctCode();
		binaryCode.op = DemcialToBinary(decimalCode.op, static_cast<int>(EBits::op));
		binaryCode.rs = DemcialToBinary(decimalCode.rs, static_cast<int>(EBits::rs));
		binaryCode.rt = DemcialToBinary(decimalCode.rt, static_cast<int>(EBits::rt));
		binaryCode.rd = DemcialToBinary(decimalCode.rd, static_cast<int>(EBits::rd));
		binaryCode.shamt = DemcialToBinary(decimalCode.shamt, static_cast<int>(EBits::shamt));
		binaryCode.funct = DemcialToBinary(decimalCode.funct, static_cast<int>(EBits::funct));
		machineCode = binaryCode.op + binaryCode.rs + binaryCode.rt + binaryCode.rd + binaryCode.shamt + binaryCode.funct;
	}
	if(opType == 'i') {
		SetOpCode();
		binaryCode.op = DemcialToBinary(decimalCode.op, static_cast<int>(EBits::op));
		binaryCode.rs = DemcialToBinary(decimalCode.rs, static_cast<int>(EBits::rs));
		binaryCode.rt = DemcialToBinary(decimalCode.rt, static_cast<int>(EBits::rt));
		binaryCode.address = DemcialToBinary(decimalCode.address, static_cast<int>(EBits::address));
		machineCode = binaryCode.op + binaryCode.rs + binaryCode.rt + binaryCode.address;
	}
}

void MipsToMC::SetFunctCode() {
	if (order == "add")
		decimalCode.funct = static_cast<int>(EFunct::add);
	if (order == "sub")
		decimalCode.funct = static_cast<int>(EFunct::sub);
}

ostream& operator<<(ostream& os, MipsToMC& mipsToMC) {
	if (mipsToMC.opType == 'e')
		os << "Your instruction is error, so it can't convert to machine code.\n";
	else
		os << OutputMC(mipsToMC.machineCode) << "\n";
	return os;
}