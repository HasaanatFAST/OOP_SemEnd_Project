#ifndef PRESCRIPTION_H
#define PRESCRIPTION_H

#include <iostream>
#include <string>
using namespace std;

class Prescription {
private:
    int prescriptionId, appointmentId, patientId, doctorId;
    string date, medicines, notes;

public:
    Prescription();
    Prescription(int pid, int aid, int patId, int did, const string& d,
                 const string& med, const string& n);

    int getId() const;
    int getPrescriptionId() const;
    int getAppointmentId() const;
    int getPatientId() const;
    int getDoctorId() const;
    const string& getDate() const;
    const string& getMedicines() const;
    const string& getNotes() const;

    void setPrescriptionId(int id);
    void setAppointmentId(int id);
    void setPatientId(int id);
    void setDoctorId(int id);
    void setDate(const string& d);
    void setMedicines(const string& m);
    void setNotes(const string& n);
};

#endif
