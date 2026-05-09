#ifndef ADMINMENU_H
#define ADMINMENU_H

#include <ctime>
#include <string>
#include "Admin.h"
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

class AdminMenu {
private:
    Admin* admin;
    Storage<Patient>* patients;
    Storage<Doctor>* doctors;
    Storage<Appointment>* appointments;
    Storage<Bill>* bills;
    Storage<Prescription>* prescriptions;
    FileHandler fh;
    Validator v;

    string getToday() const;
    int getMaxDocId();
    string buildAllPats();
    string buildAllDocs();
    string buildAllAppts();
    string buildUnpaid();
    string buildSecLog();
    string buildReport();

public:
    AdminMenu(Admin* a, Storage<Patient>* p, Storage<Doctor>* d,
              Storage<Appointment>* ap, Storage<Bill>* b, Storage<Prescription>* pr);
    void run(sf::RenderWindow& w, sf::Font& f);
};

#endif
