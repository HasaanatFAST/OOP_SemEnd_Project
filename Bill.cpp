#include "Bill.h"

// Default constructor
Bill::Bill() : billId(0), patientId(0), appointmentId(0), amount(0.0f) {
}

// Parameterized constructor
Bill::Bill(int bid, int pid, int aid, float amt, const string& st, const string& d)
    : billId(bid), patientId(pid), appointmentId(aid), amount(amt), status(st), date(d) {
}

// Getters
int Bill::getId() const {
    return billId;
}

int Bill::getBillId() const {
    return billId;
}

int Bill::getPatientId() const {
    return patientId;
}

int Bill::getAppointmentId() const {
    return appointmentId;
}

float Bill::getAmount() const {
    return amount;
}

const string& Bill::getStatus() const {
    return status;
}

const string& Bill::getDate() const {
    return date;
}

// Setters
void Bill::setBillId(int id) {
    billId = id;
}

void Bill::setPatientId(int id) {
    patientId = id;
}

void Bill::setAppointmentId(int id) {
    appointmentId = id;
}

void Bill::setAmount(float a) {
    amount = a;
}

void Bill::setStatus(const string& st) {
    status = st;
}

void Bill::setDate(const string& d) {
    date = d;
}
