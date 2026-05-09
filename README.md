# MediCore Hospital Management System

**Course:** Object Oriented Programming (OOP)  
**Semester:** Spring 2026  
**Section:** BCS-2A

## GitHub Repository
https://github.com/YOUR_USERNAME/HospitalMS

*(Replace this link with your actual GitHub repository URL before submitting)*

---

## How to Compile

Make sure you have `g++` installed. Navigate to the project folder and run:

```
g++ -std=c++17 -o hospital main.cpp
```

## How to Run

```
./hospital
```

On Windows:
```
hospital.exe
```

---

## How to Use

When the program starts, you will see the main menu:

```
Welcome to MediCore Hospital Management System
===============================================
Login as:
1. Patient
2. Doctor
3. Admin
4. Exit
```

Choose your role and enter your ID and password. You have 3 attempts before being locked out.

---

## Required .txt Files

These files must exist in the **same folder** as the executable before running:

| File | Purpose |
|------|---------|
| `admin.txt` | Admin login credentials |
| `patients.txt` | Patient records |
| `doctors.txt` | Doctor records |
| `appointments.txt` | Appointment records (can be empty) |
| `bills.txt` | Bill records (can be empty) |
| `prescriptions.txt` | Prescription records (can be empty) |
| `security_log.txt` | Failed login attempts (can be empty) |

Sample data is included in the zip.

---

## File Formats (CSV, comma-separated)

**admin.txt**
```
admin_id,name,password
1,Admin,admin123
```

**patients.txt**
```
patient_id,name,age,gender,contact,password,balance
1,Ahmed Ali,28,M,03001234567,pass123,5000.00
```

**doctors.txt**
```
doctor_id,name,specialization,contact,password,fee
1,Dr. Sara Khan,Cardiology,03211234567,doc456,1500.00
```

**appointments.txt**
```
appointment_id,patient_id,doctor_id,date,time_slot,status
1,1,1,26-04-2026,09:00,pending
```

**bills.txt**
```
bill_id,patient_id,appointment_id,amount,status,date
1,1,1,1500.00,unpaid,26-04-2026
```

**prescriptions.txt**
```
prescription_id,appointment_id,patient_id,doctor_id,date,medicines,notes
1,1,1,1,26-04-2026,Paracetamol 500mg,Take after meals
```

---

## Project Structure

| File | Description |
|------|-------------|
| `main.cpp` | Entry point. Loads all data, handles login routing |
| `Person.h` | Abstract base class for all users |
| `Patient.h` | Patient class with operator overloads (+= -= == <<) |
| `Doctor.h` | Doctor class with operator overloads (== <<) |
| `Admin.h` | Admin class |
| `Appointment.h` | Appointment class with operator overloads (== <<) |
| `Bill.h` | Bill class |
| `Prescription.h` | Prescription class |
| `Storage.h` | Generic template class for storing any entity |
| `FileHandler.h` | All file I/O operations |
| `Validator.h` | All input validation logic |
| `HospitalException.h` | Custom exception classes |
| `PatientMenu.h` | Patient menu and all patient actions |
| `DoctorMenu.h` | Doctor menu and all doctor actions |
| `AdminMenu.h` | Admin menu and all admin actions |

---

## Default Login Credentials (for testing)

| Role | ID | Password |
|------|----|----------|
| Admin | 1 | admin123 |
| Patient | 1 | pass123 |
| Patient | 2 | pass456 |
| Doctor | 1 | doc456 |
| Doctor | 2 | doc789 |

---

## Notes

- No `std::vector`, `strcmp()`, `strtok()`, or static arrays used.
- All pointer allocations are dynamic.
- All data is read from and written to `.txt` files immediately.
- `Storage<T>` uses an internal array of size 100.
- `FileHandler` is the only class that performs file I/O.
- `Validator` is the only class that handles validation logic.
- Memory allocated with `new` is deleted with `delete` where used.
