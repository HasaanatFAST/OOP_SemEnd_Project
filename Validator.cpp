#include "Validator.h"

// Character checks
bool Validator::isDigit(char c) const {
    return c >= '0' && c <= '9';
}

bool Validator::isAlpha(char c) const {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

char Validator::toLower(char c) const {
    return (c >= 'A' && c <= 'Z') ? c + 32 : c;
}

// Validate contact number (must be 11 digits)
bool Validator::isValidContact(const string& contact) const {
    if (contact.size() != 11) return false;
    for (int i = 0; i < 11; i++) {
        if (!isDigit(contact[i])) return false;
    }
    return true;
}

// Validate password (minimum 6 characters)
bool Validator::isValidPassword(const string& pass) const {
    return pass.size() >= 6;
}

// Validate date format DD-MM-YYYY
bool Validator::isValidDate(const string& date, int currentYear) const {
    if (date.size() != 10) return false;
    if (date[2] != '-' || date[5] != '-') return false;

    for (int i = 0; i < 10; i++) {
        if (i == 2 || i == 5) continue;
        if (!isDigit(date[i])) return false;
    }

    int day = (date[0] - '0') * 10 + (date[1] - '0');
    int month = (date[3] - '0') * 10 + (date[4] - '0');
    int year = (date[6] - '0') * 1000 + (date[7] - '0') * 100
             + (date[8] - '0') * 10 + (date[9] - '0');

    if (day < 1 || day > 31) return false;
    if (month < 1 || month > 12) return false;
    if (year < currentYear) return false;

    return true;
}

// Validate time slot (must be one of the hospital hours)
bool Validator::isValidTimeSlot(const string& slot) const {
    const char* slots[8] = {
        "09:00", "10:00", "11:00", "12:00",
        "13:00", "14:00", "15:00", "16:00"
    };
    for (int i = 0; i < 8; i++) {
        if (slot == slots[i]) return true;
    }
    return false;
}

// Other validators
bool Validator::isPositiveFloat(float val) const {
    return val > 0.0f;
}

bool Validator::isValidMenuChoice(int choice, int min, int max) const {
    return choice >= min && choice <= max;
}

bool Validator::isValidId(int id) const {
    return id > 0;
}

// Case-insensitive string comparison
bool Validator::strEqIgnoreCase(const string& a, const string& b) const {
    if (a.size() != b.size()) return false;
    for (int i = 0; i < (int)a.size(); i++) {
        if (toLower(a[i]) != toLower(b[i])) return false;
    }
    return true;
}
