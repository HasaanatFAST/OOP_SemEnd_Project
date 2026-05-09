#include "Appointment.h"

// Default constructor
Appointment::Appointment() : appointmentId(0), patientId(0), doctorId(0) {
}

// Parameterized constructor
Appointment::Appointment(int aid, int pid, int did, const string& d, const string& ts, const string& st)
    : appointmentId(aid), patientId(pid), doctorId(did), date(d), timeSlot(ts), status(st) {
}

// Equality operator
bool Appointment::operator==(const Appointment& other) const {
    if (doctorId != other.doctorId) return false;
    if (date != other.date) return false;
    if (timeSlot != other.timeSlot) return false;
    if (status == "cancelled" || other.status == "cancelled") return false;
    return true;
}

// Stream insertion operator
ostream& operator<<(ostream& out, const Appointment& a) {
    out << "ID: " << a.appointmentId << " | PatientID: " << a.patientId
        << " | DoctorID: " << a.doctorId << " | Date: " << a.date
        << " | Time: " << a.timeSlot << " | Status: " << a.status;
    return out;
}

// Getters
int Appointment::getId() const {
    return appointmentId;
}

int Appointment::getAppointmentId() const {
    return appointmentId;
}

int Appointment::getPatientId() const {
    return patientId;
}

int Appointment::getDoctorId() const {
    return doctorId;
}

const string& Appointment::getDate() const {
    return date;
}

const string& Appointment::getTimeSlot() const {
    return timeSlot;
}

const string& Appointment::getStatus() const {
    return status;
}

// Setters
void Appointment::setAppointmentId(int id) {
    appointmentId = id;
}

void Appointment::setPatientId(int id) {
    patientId = id;
}

void Appointment::setDoctorId(int id) {
    doctorId = id;
}

void Appointment::setDate(const string& d) {
    date = d;
}

void Appointment::setTimeSlot(const string& ts) {
    timeSlot = ts;
}

void Appointment::setStatus(const string& st) {
    status = st;
}
