#ifndef HOSPITALEXCEPTION_H
#define HOSPITALEXCEPTION_H

#include <string>
using namespace std;

class HospitalException {
protected:
    string message;
public:
    HospitalException(const string& msg);
    virtual const string& what() const;
    virtual ~HospitalException();
};

class FileNotFoundException : public HospitalException {
public:
    FileNotFoundException(const string& msg);
};

class InsufficientFundsException : public HospitalException {
public:
    InsufficientFundsException(const string& msg);
};

class InvalidInputException : public HospitalException {
public:
    InvalidInputException(const string& msg);
};

class SlotUnavailableException : public HospitalException {
public:
    SlotUnavailableException(const string& msg);
};

#endif
