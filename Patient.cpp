#include "Patient.h"

// Default constructor
Patient::Patient() : Person(), age(0), balance(0.0f) {
}

// Parameterized constructor
Patient::Patient(int id, const string& name, int age, const string& gender,
                 const string& contact, const string& password, float balance)
    : Person(id, name, password, contact), age(age), gender(gender), balance(balance) {
}

// Operator overloads
Patient& Patient::operator+=(float amount) {
    balance += amount;
    return *this;
}

Patient& Patient::operator-=(float amount) {
    balance -= amount;
    return *this;
}

bool Patient::operator==(const Patient& other) const {
    return id == other.id;
}

ostream& operator<<(ostream& out, const Patient& p) {
    out << "ID: " << p.id << " | Name: " << p.getName()
        << " | Age: " << p.age << " | Gender: " << p.gender
        << " | Contact: " << p.getContact()
        << " | Balance: PKR " << p.balance;
    return out;
}

// Display info
void Patient::displayInfo() const {
    cout << *this << endl;
}

// Display menu
void Patient::displayMenu() const {
    cout << "\nWelcome, " << getName() << endl;
    cout << "Balance: PKR " << balance << endl;
    cout << "========================" << endl;
    cout << "1. Book Appointment" << endl;
    cout << "2. Cancel Appointment" << endl;
    cout << "3. View My Appointments" << endl;
    cout << "4. View My Medical Records" << endl;
    cout << "5. View My Bills" << endl;
    cout << "6. Pay Bill" << endl;
    cout << "7. Top Up Balance" << endl;
    cout << "8. Logout" << endl;
}

// Getters
int Patient::getAge() const {
    return age;
}

const string& Patient::getGender() const {
    return gender;
}

float Patient::getBalance() const {
    return balance;
}

// Setters
void Patient::setAge(int a) {
    age = a;
}

void Patient::setGender(const string& g) {
    gender = g;
}

void Patient::setBalance(float b) {
    balance = b;
}
