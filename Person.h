#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <string>
using namespace std;

class Person {
protected:
    int id;
    string name;
    string password;
    string contact;

public:
    Person();
    Person(int id, const string& name, const string& password, const string& contact);

    int getId() const;
    void setId(int i);
    const string& getName() const;
    void setName(const string& n);
    const string& getPassword() const;
    void setPassword(const string& p);
    const string& getContact() const;
    void setContact(const string& c);

    virtual void displayInfo() const = 0;
    virtual void displayMenu() const = 0;
    virtual ~Person();
};

#endif
