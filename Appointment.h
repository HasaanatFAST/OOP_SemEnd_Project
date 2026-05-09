#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include <iostream>
#include <string>
using namespace std;

class Appointment {
private:
    int appointmentId, patientId, doctorId;
    string date, timeSlot, status;

public:
    Appointment();
    Appointment(int aid, int pid, int did, const string& d, const string& ts, const string& st);

    bool operator==(const Appointment& other) const;

    friend ostream& operator<<(ostream& out, const Appointment& a);

    int getId() const;
    int getAppointmentId() const;
    int getPatientId() const;
    int getDoctorId() const;
    const string& getDate() const;
    const string& getTimeSlot() const;
    const string& getStatus() const;

    void setAppointmentId(int id);
    void setPatientId(int id);
    void setDoctorId(int id);
    void setDate(const string& d);
    void setTimeSlot(const string& ts);
    void setStatus(const string& st);
};

#endif
