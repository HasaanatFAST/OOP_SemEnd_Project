#include "Doctor.h"

// Default constructor
Doctor::Doctor() : Person(), fee(0.0f) {
}

// Parameterized constructor
Doctor::Doctor(int id, const string& name, const string& spec, const string& contact,
               const string& password, float fee)
    : Person(id, name, password, contact), specialization(spec), fee(fee) {
}

// Operator overloads
bool Doctor::operator==(const Doctor& other) const {
    return id == other.id;
}

ostream& operator<<(ostream& out, const Doctor& d) {
    out << "ID: " << d.id << " | Name: " << d.getName()
        << " | Specialization: " << d.specialization
        << " | Contact: " << d.getContact()
        << " | Fee: PKR " << d.fee;
    return out;
}

// Display info
void Doctor::displayInfo() const {
    cout << *this << endl;
}

// Display menu
void Doctor::displayMenu() const {
    cout << "\nWelcome, Dr. " << getName() << " | Specialization: " << specialization << endl;
    cout << "===============================================" << endl;
    cout << "1. View Today's Appointments" << endl;
    cout << "2. Mark Appointment Complete" << endl;
    cout << "3. Mark Appointment No-Show" << endl;
    cout << "4. Write Prescription" << endl;
    cout << "5. View Patient Medical History" << endl;
    cout << "6. Logout" << endl;
}

// Getters
const string& Doctor::getSpecialization() const {
    return specialization;
}

float Doctor::getFee() const {
    return fee;
}

// Setters
void Doctor::setSpecialization(const string& s) {
    specialization = s;
}

void Doctor::setFee(float f) {
    fee = f;
}
