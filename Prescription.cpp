#include "Prescription.h"

// Default constructor
Prescription::Prescription() : prescriptionId(0), appointmentId(0), patientId(0), doctorId(0) {
}

// Parameterized constructor
Prescription::Prescription(int pid, int aid, int patId, int did, const string& d,
                           const string& med, const string& n)
    : prescriptionId(pid), appointmentId(aid), patientId(patId), doctorId(did),
      date(d), medicines(med), notes(n) {
}

// Getters
int Prescription::getId() const {
    return prescriptionId;
}

int Prescription::getPrescriptionId() const {
    return prescriptionId;
}

int Prescription::getAppointmentId() const {
    return appointmentId;
}

int Prescription::getPatientId() const {
    return patientId;
}

int Prescription::getDoctorId() const {
    return doctorId;
}

const string& Prescription::getDate() const {
    return date;
}

const string& Prescription::getMedicines() const {
    return medicines;
}

const string& Prescription::getNotes() const {
    return notes;
}

// Setters
void Prescription::setPrescriptionId(int id) {
    prescriptionId = id;
}

void Prescription::setAppointmentId(int id) {
    appointmentId = id;
}

void Prescription::setPatientId(int id) {
    patientId = id;
}

void Prescription::setDoctorId(int id) {
    doctorId = id;
}

void Prescription::setDate(const string& d) {
    date = d;
}

void Prescription::setMedicines(const string& m) {
    medicines = m;
}

void Prescription::setNotes(const string& n) {
    notes = n;
}
