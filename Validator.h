#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <string>
using namespace std;

class Validator {
public:
    bool isDigit(char c) const;
    bool isAlpha(char c) const;
    char toLower(char c) const;
    bool isValidContact(const string& contact) const;
    bool isValidPassword(const string& pass) const;
    bool isValidDate(const string& date, int currentYear) const;
    bool isValidTimeSlot(const string& slot) const;
    bool isPositiveFloat(float val) const;
    bool isValidMenuChoice(int choice, int min, int max) const;
    bool isValidId(int id) const;
    bool strEqIgnoreCase(const string& a, const string& b) const;
};

#endif
