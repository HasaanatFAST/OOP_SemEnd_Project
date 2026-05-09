#include "Admin.h"

// Default constructor
Admin::Admin() : Person() {
}

// Parameterized constructor
Admin::Admin(int id, const string& name, const string& password)
    : Person(id, name, password, "") {
}

// Display admin info
void Admin::displayInfo() const {
    cout << "Admin ID: " << id << " | Name: " << getName() << endl;
}

// Display admin menu options
void Admin::displayMenu() const {
    cout << "\nAdmin Panel - MediCore\n======================" << endl;
    cout << "1. Add Doctor" << endl;
    cout << "2. Remove Doctor" << endl;
    cout << "3. View All Patients" << endl;
    cout << "4. View All Doctors" << endl;
    cout << "5. View All Appointments" << endl;
    cout << "6. View Unpaid Bills" << endl;
    cout << "7. Discharge Patient" << endl;
    cout << "8. View Security Log" << endl;
    cout << "9. Generate Daily Report" << endl;
    cout << "10. Logout" << endl;
}
