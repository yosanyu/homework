#include<string>
#include<vector>
#include<thread>

using namespace std; 

#ifndef __function_H_
#define __function_H_
#endif

void Start();
void Input(vector<string>& instruction);
void EndThread(thread* threads,const int size);
int StringToInt(string &convert);
int Power(const int x,const int pow);
string DemcialToBinary(int covert, const int& bits);
string OutputMC(string& machineCode);
bool IsAddress(string& address);