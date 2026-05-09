#ifndef PATIENT_H
#define PATIENT_H

#include "Person.h"
#include <iostream>
#include <string>
using namespace std;

class Patient : public Person {
private:
    int age;
    string gender;
    float balance;

public:
    Patient();
    Patient(int id, const string& name, int age, const string& gender,
            const string& contact, const string& password, float balance);

    Patient& operator+=(float amount);
    Patient& operator-=(float amount);
    bool operator==(const Patient& other) const;

    friend ostream& operator<<(ostream& out, const Patient& p);

    void displayInfo() const;
    void displayMenu() const;

    int getAge() const;
    const string& getGender() const;
    float getBalance() const;
    void setAge(int a);
    void setGender(const string& g);
    void setBalance(float b);
};

#endif
