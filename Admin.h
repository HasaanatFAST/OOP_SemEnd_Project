#ifndef ADMIN_H
#define ADMIN_H

#include "Person.h"
#include <iostream>
#include <string>
using namespace std;

class Admin : public Person {
public:
    Admin();
    Admin(int id, const string& name, const string& password);

    void displayInfo() const;
    void displayMenu() const;
};

#endif
