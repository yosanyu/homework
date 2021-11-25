#pragma once
#include <queue>
#include <mutex>
#include <condition_variable>

using std::queue;
using std::mutex;
using std::condition_variable;

enum class DoctorStatus {
	Idle,
	Working
};

enum class PatientStatus {
	NotInClinlc,
	InClinlc,
	Waiting,
	InTreatment,
	Fever
};

class Clinic {
public:
	Clinic();
	void Visit(int patientNumber);
	void Heal(int patientNumber);
	void Leave(int patientNumber);
	void Leave(int patientNumber, int doctorNumber);
private:
	DoctorStatus doctors[3];
	PatientStatus patients[20];
	condition_variable patientsCV[20];
	queue<int> waitingRoom;
	mutex mutexLeave;
};

void Delay(int milliSecond);