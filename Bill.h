#ifndef BILL_H
#define BILL_H

#include <iostream>
#include <string>
using namespace std;

class Bill {
private:
    int billId, patientId, appointmentId;
    float amount;
    string status, date;

public:
    Bill();
    Bill(int bid, int pid, int aid, float amt, const string& st, const string& d);

    int getId() const;
    int getBillId() const;
    int getPatientId() const;
    int getAppointmentId() const;
    float getAmount() const;
    const string& getStatus() const;
    const string& getDate() const;

    void setBillId(int id);
    void setPatientId(int id);
    void setAppointmentId(int id);
    void setAmount(float a);
    void setStatus(const string& st);
    void setDate(const string& d);
};

#endif
