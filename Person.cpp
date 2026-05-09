#include "Person.h"

// Default constructor
Person::Person() : id(0) {
}

// Parameterized constructor
Person::Person(int id, const string& name, const string& password, const string& contact)
    : id(id), name(name), password(password), contact(contact) {
}

// Getters
int Person::getId() const {
    return id;
}

const string& Person::getName() const {
    return name;
}

const string& Person::getPassword() const {
    return password;
}

const string& Person::getContact() const {
    return contact;
}

// Setters
void Person::setId(int i) {
    id = i;
}

void Person::setName(const string& n) {
    name = n;
}

void Person::setPassword(const string& p) {
    password = p;
}

void Person::setContact(const string& c) {
    contact = c;
}

// Destructor
Person::~Person() {
}
