#ifndef DOCTOR_H
#define DOCTOR_H

#include "Person.h"
#include <iostream>
#include <string>
using namespace std;

class Doctor : public Person {
private:
    string specialization;
    float fee;

public:
    Doctor();
    Doctor(int id, const string& name, const string& spec, const string& contact,
           const string& password, float fee);

    bool operator==(const Doctor& other) const;

    friend ostream& operator<<(ostream& out, const Doctor& d);

    void displayInfo() const;
    void displayMenu() const;

    const string& getSpecialization() const;
    float getFee() const;
    void setSpecialization(const string& s);
    void setFee(float f);
};

#endif
