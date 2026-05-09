#ifndef PATIENTMENU_H
#define PATIENTMENU_H

#include <ctime>
#include <string>
#include "Patient.h"
#include "Doctor.h"
#include "Appointment.h"
#include "Bill.h"
#include "Prescription.h"
#include "Storage.h"
#include "FileHandler.h"
#include "Validator.h"
#include "HospitalException.h"
#include "GUI.h"

using namespace std;

class PatientMenu {
private:
    Patient* patient;
    Storage<Doctor>* doctors;
    Storage<Appointment>* appointments;
    Storage<Bill>* bills;
    Storage<Prescription>* prescriptions;
    FileHandler fh;
    Validator v;

    string getTodayDate() const;
    int getCurrentYear() const;
    int getMaxApptId();
    int getMaxBillId();
    int cmpDates(const string& a, const string& b) const;
    string buildApptList();
    string buildMedRecords();
    string buildBillList();
    string buildDocsBySpec(const string& sp);
    string buildSlots(int did, const string& dt);
    string buildPending();
    string buildUnpaid();

public:
    PatientMenu(Patient* p, Storage<Doctor>* d, Storage<Appointment>* a,
                Storage<Bill>* b, Storage<Prescription>* pr);
    void run(Storage<Patient>& ps, sf::RenderWindow& w, sf::Font& f);
};

#endif
