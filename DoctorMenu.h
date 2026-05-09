#ifndef DOCTORMENU_H
#define DOCTORMENU_H

#include <ctime>
#include <string>
#include "Doctor.h"
#include "Patient.h"
#include "Appointment.h"
#include "Prescription.h"
#include "Bill.h"
#include "Storage.h"
#include "FileHandler.h"
#include "GUI.h"

using namespace std;

class DoctorMenu {
private:
    Doctor* doctor;
    Storage<Patient>* patients;
    Storage<Appointment>* appointments;
    Storage<Prescription>* prescriptions;
    Storage<Bill>* bills;
    FileHandler fh;

    string getToday() const;
    int getMaxPrescId();
    string buildTodayAppts();
    string buildPendingToday();
    string buildPatHist(int pid);

public:
    DoctorMenu(Doctor* d, Storage<Patient>* p, Storage<Appointment>* a,
               Storage<Prescription>* pr, Storage<Bill>* b);
    void run(sf::RenderWindow& w, sf::Font& f);
};

#endif
