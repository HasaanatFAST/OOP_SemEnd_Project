#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include "Patient.h"
#include "Doctor.h"
#include "Admin.h"
#include "Appointment.h"
#include "Bill.h"
#include "Prescription.h"
#include "Storage.h"
#include "HospitalException.h"

using namespace std;

class FileHandler {
public:
    // Manual int-to-string
    string intToStr(int val) const;
    // Manual string-to-int
    int strToInt(const string& s) const;
    // Manual string-to-float
    float strToFloat(const string& s) const;
    // Manual float-to-string (2 decimal places)
    string floatToStr(float val) const;
    // Parse a comma-separated token from line starting at idx
    void parseToken(const char* line, int& idx, string& dest) const;

    // ====== Load functions ======
    void loadPatients(Storage<Patient>& storage);
    void loadDoctors(Storage<Doctor>& storage);
    void loadAdmin(Admin& admin);
    void loadAppointments(Storage<Appointment>& storage);
    void loadBills(Storage<Bill>& storage);
    void loadPrescriptions(Storage<Prescription>& storage);

    // ====== Save functions ======
    void saveAllPatients(Storage<Patient>& s);
    void saveAllDoctors(Storage<Doctor>& s);
    void saveAllAppointments(Storage<Appointment>& s);
    void saveAllBills(Storage<Bill>& s);
    void saveAllPrescriptions(Storage<Prescription>& s);

    // ====== Append functions ======
    void appendPatient(const Patient& p);
    void appendDoctor(const Doctor& d);
    void appendAppointment(const Appointment& a);
    void appendBill(const Bill& b);
    void appendPrescription(const Prescription& pr);

    void logSecurityEvent(const string& role, const string& enteredId, const string& result);
    void readSecurityLog(string& out);
    void archivePatient(const Patient& p, Storage<Appointment>& apps,
                        Storage<Bill>& bills, Storage<Prescription>& prescs);
};

#endif
