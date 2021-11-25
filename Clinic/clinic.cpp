#include <iostream>
#include <cstdlib>
#include <ctime>
#include <mutex>
#include "clinic.h"

using std::cout;
using std::mutex;
using std::unique_lock;

Clinic::Clinic() {
	for (int i = 0; i < 3; i++)
		doctors[i] = DoctorStatus::Idle;
	for (int i = 0; i < 20; i++)
		patients[i] = PatientStatus::NotInClinlc;
}

void Clinic::Visit(int patientNumber) {

	patients[patientNumber] = PatientStatus::InClinlc;

	srand(unsigned(time(NULL)));

	float temperature = 35.0 +(rand() % 41) / 10.0;

	bool bHasFever = false;
	if (temperature >= 37.5)
		bHasFever = true;

	if (bHasFever) {
		patients[patientNumber] = PatientStatus::Fever;
		Leave(patientNumber);
		return;
	}

	else {

		Heal(patientNumber);

		if (patients[patientNumber] == PatientStatus::Waiting) {
			mutex mutexWait;
			unique_lock<mutex> Lock(mutexWait);
			patientsCV[patientNumber].wait(Lock);
			Heal(patientNumber);
		}
		return;
	}

}

void Clinic::Heal(int patientNumber) {

	for (int i = 0; i < 3; i++) {
		if (doctors[i] == DoctorStatus::Idle) {
			doctors[i] = DoctorStatus::Working;
			cout << "No." << patientNumber+1 << " patient";

			if (patients[patientNumber] == PatientStatus::InClinlc)
				cout << " goes into the consulting room to see No." << i+1 << " doctor.\n\n";

			if (patients[patientNumber] == PatientStatus::Waiting)
				cout << " from waiting room goes into the consulting room to see No." << i+1 << " doctor.\n\n";

			patients[patientNumber] = PatientStatus::InTreatment;

			Delay((rand() % 5 + 8) * 1000);

			mutexLeave.lock();
			Leave(patientNumber, i);
			mutexLeave.unlock();

			return;
		}
	}
	if (patients[patientNumber] == PatientStatus::InClinlc) {
		if (waitingRoom.size() < 4) {
			patients[patientNumber] = PatientStatus::Waiting;
			waitingRoom.push(patientNumber);
			cout << "No." << patientNumber+1 << " patient" << " goes into the waiting room.\n\n";
			return;
		}

		else {
			cout << "No seat, so No." << patientNumber+1 << " patient left the clinic.\n\n";
			return;
		}
	}

}

void Clinic::Leave(int patientNumber) {
	cout << "No." << patientNumber+1 << " patient" << " has a fever, so he left the clinic.\n\n";
	patients[patientNumber] = PatientStatus::NotInClinlc;
	return;
}

void Clinic::Leave(int patientNumber, int doctorNumber) {
	cout << "No." << patientNumber+1 << " patient end the treatment, so he left the clinic.\n\n";
	patients[patientNumber] = PatientStatus::NotInClinlc;
	doctors[doctorNumber] = DoctorStatus::Idle;
	if (!waitingRoom.empty()) {
		int current = waitingRoom.front();
		waitingRoom.pop();
		patientsCV[current].notify_all();
	}
	return;
}

void Delay(int milliSecond) {
	clock_t begin = clock();
	while (clock() - begin <= milliSecond);
}
