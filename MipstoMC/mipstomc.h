#include<string>

using namespace std;
#ifndef __mipstomc_H_
#define __mipstomc_H_
#endif

// define struct

struct DecimalCode {
	int op;
	int rs;
	int rt;
	int rd;
	int shamt;
	int funct;
	int address;
};

struct BinaryCode {
	string op;
	string rs;
	string rt;
	string rd;
	string shamt;
	string funct;
	string address;
};

struct RegisterValue {
	int number;
	string name;
	RegisterValue();
};

// enumerate funct's value and every element's bits in machine code.

enum class EFunct : int {
	add = 32,
	sub = 34
};

enum class EBits : int {
	op = 6,
	rs = 5,
	rt = 5,
	rd = 5,
	shamt = 5,
	funct = 6,
	address = 16
};

// define class
// The method of class, if its implementation use only an instruction, then use inline.
// Becuase we can get better performance.

class MipsToMC {
public:
	MipsToMC();
	void SetInstruction(string& instruction) {inputInstruction = instruction;};
	void InstructionProcess();
	void FindLabel();
	void CheckType();
	void ChoiceType();
	void RType();
	void IType();
	void SetErrorType() {opType = 'e';};
	void SetOpCode();
	void SetShamtCode() {decimalCode.shamt = 0;};
	void SetFunctCode();
	void SetAddress(string address);
	void SetAddress(int address) {decimalCode.address = address;};
	void SetMachineCode();
	string GetOrder() {return order;};
	string GetLabel() { return label;};
	// operator overloading
	friend ostream& operator<<(ostream& os, MipsToMC& mipsToMC);
private:
	DecimalCode decimalCode;
	BinaryCode binaryCode;
	string inputInstruction;
	string afterProcessInstruction;
	string order;
	string machineCode;
	string label;
	int instructionIndex;
	char opType;
};
