#include "HospitalException.h"

// Base exception
HospitalException::HospitalException(const string& msg) : message(msg) {
}

const string& HospitalException::what() const {
    return message;
}

HospitalException::~HospitalException() {
}

// Derived exceptions
FileNotFoundException::FileNotFoundException(const string& msg)
    : HospitalException(msg) {
}

InsufficientFundsException::InsufficientFundsException(const string& msg)
    : HospitalException(msg) {
}

InvalidInputException::InvalidInputException(const string& msg)
    : HospitalException(msg) {
}

SlotUnavailableException::SlotUnavailableException(const string& msg)
    : HospitalException(msg) {
}
