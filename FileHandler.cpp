#include "FileHandler.h"

// Manual int-to-string
string FileHandler::intToStr(int val) const {
    if (val == 0) return "0";
    string result;
    bool neg = val < 0; if (neg) val = -val;
    while (val > 0) { result = char('0' + val % 10) + result; val /= 10; }
    if (neg) result = "-" + result;
    return result;
}

// Manual string-to-int
int FileHandler::strToInt(const string& s) const {
    int result = 0, i = 0; bool neg = false;
    if (s.size() > 0 && s[0] == '-') { neg = true; i++; }
    for (; i < (int)s.size(); i++)
        if (s[i] >= '0' && s[i] <= '9') result = result * 10 + (s[i] - '0');
    return neg ? -result : result;
}

// Manual string-to-float
float FileHandler::strToFloat(const string& s) const {
    float result = 0, frac = 0, div = 10;
    bool afterDot = false;
    for (int i = 0; i < (int)s.size(); i++) {
        if (s[i] == '.') afterDot = true;
        else if (s[i] >= '0' && s[i] <= '9') {
            if (!afterDot) result = result * 10 + (s[i] - '0');
            else { frac += (s[i] - '0') / div; div *= 10; }
        }
    }
    return result + frac;
}

// Manual float-to-string (2 decimal places)
string FileHandler::floatToStr(float val) const {
    int ip = (int)val;
    int fp = (int)((val - ip) * 100 + 0.5f);
    string r = intToStr(ip) + ".";
    if (fp < 10) r += "0";
    r += intToStr(fp);
    return r;
}

// Parse a comma-separated token from line starting at idx
void FileHandler::parseToken(const char* line, int& idx, string& dest) const {
    dest = "";
    while (line[idx] != ',' && line[idx] != '\n' && line[idx] != '\0') {
        dest += line[idx]; idx++;
    }
    if (line[idx] == ',') idx++;
}

// ====== Load functions ======

void FileHandler::loadPatients(Storage<Patient>& storage) {
    ifstream file("patients.txt");
    if (!file.is_open()) return;
    char line[300];
    while (file.getline(line, 300)) {
        if (line[0] == '\0') continue;
        int idx = 0;
        string idS, name, ageS, gender, contact, pass, balS;
        parseToken(line, idx, idS); parseToken(line, idx, name);
        parseToken(line, idx, ageS); parseToken(line, idx, gender);
        parseToken(line, idx, contact); parseToken(line, idx, pass);
        parseToken(line, idx, balS);
        storage.add(Patient(strToInt(idS), name, strToInt(ageS), gender, contact, pass, strToFloat(balS)));
    }
    file.close();
}

void FileHandler::loadDoctors(Storage<Doctor>& storage) {
    ifstream file("doctors.txt");
    if (!file.is_open()) return;
    char line[300];
    while (file.getline(line, 300)) {
        if (line[0] == '\0') continue;
        int idx = 0;
        string idS, name, spec, contact, pass, feeS;
        parseToken(line, idx, idS); parseToken(line, idx, name);
        parseToken(line, idx, spec); parseToken(line, idx, contact);
        parseToken(line, idx, pass); parseToken(line, idx, feeS);
        storage.add(Doctor(strToInt(idS), name, spec, contact, pass, strToFloat(feeS)));
    }
    file.close();
}

void FileHandler::loadAdmin(Admin& admin) {
    ifstream file("admin.txt");
    if (!file.is_open()) throw FileNotFoundException("admin.txt not found!");
    char line[200];
    file.getline(line, 200);
    if (line[0] == '\0') throw FileNotFoundException("admin.txt is empty!");
    int idx = 0;
    string idS, name, pass;
    parseToken(line, idx, idS); parseToken(line, idx, name); parseToken(line, idx, pass);
    admin = Admin(strToInt(idS), name, pass);
    file.close();
}

void FileHandler::loadAppointments(Storage<Appointment>& storage) {
    ifstream file("appointments.txt");
    if (!file.is_open()) return;
    char line[200];
    while (file.getline(line, 200)) {
        if (line[0] == '\0') continue;
        int idx = 0;
        string aid, pid, did, date, slot, status;
        parseToken(line, idx, aid); parseToken(line, idx, pid);
        parseToken(line, idx, did); parseToken(line, idx, date);
        parseToken(line, idx, slot); parseToken(line, idx, status);
        storage.add(Appointment(strToInt(aid), strToInt(pid), strToInt(did), date, slot, status));
    }
    file.close();
}

void FileHandler::loadBills(Storage<Bill>& storage) {
    ifstream file("bills.txt");
    if (!file.is_open()) return;
    char line[200];
    while (file.getline(line, 200)) {
        if (line[0] == '\0') continue;
        int idx = 0;
        string bid, pid, aid, amt, status, date;
        parseToken(line, idx, bid); parseToken(line, idx, pid);
        parseToken(line, idx, aid); parseToken(line, idx, amt);
        parseToken(line, idx, status); parseToken(line, idx, date);
        storage.add(Bill(strToInt(bid), strToInt(pid), strToInt(aid), strToFloat(amt), status, date));
    }
    file.close();
}

void FileHandler::loadPrescriptions(Storage<Prescription>& storage) {
    ifstream file("prescriptions.txt");
    if (!file.is_open()) return;
    char line[1000];
    while (file.getline(line, 1000)) {
        if (line[0] == '\0') continue;
        int idx = 0;
        string prid, aid, patid, did, date, med, notes;
        parseToken(line, idx, prid); parseToken(line, idx, aid);
        parseToken(line, idx, patid); parseToken(line, idx, did);
        parseToken(line, idx, date); parseToken(line, idx, med);
        parseToken(line, idx, notes);
        storage.add(Prescription(strToInt(prid), strToInt(aid), strToInt(patid), strToInt(did), date, med, notes));
    }
    file.close();
}

// ====== Save functions ======

void FileHandler::saveAllPatients(Storage<Patient>& s) {
    ofstream f("patients.txt");
    Patient* a = s.getAll();
    for (int i = 0; i < s.size(); i++)
        f << a[i].getId() << "," << a[i].getName() << "," << a[i].getAge() << ","
          << a[i].getGender() << "," << a[i].getContact() << "," << a[i].getPassword()
          << "," << floatToStr(a[i].getBalance()) << "\n";
    f.close();
}

void FileHandler::saveAllDoctors(Storage<Doctor>& s) {
    ofstream f("doctors.txt");
    Doctor* a = s.getAll();
    for (int i = 0; i < s.size(); i++)
        f << a[i].getId() << "," << a[i].getName() << "," << a[i].getSpecialization()
          << "," << a[i].getContact() << "," << a[i].getPassword()
          << "," << floatToStr(a[i].getFee()) << "\n";
    f.close();
}

void FileHandler::saveAllAppointments(Storage<Appointment>& s) {
    ofstream f("appointments.txt");
    Appointment* a = s.getAll();
    for (int i = 0; i < s.size(); i++)
        f << a[i].getAppointmentId() << "," << a[i].getPatientId() << ","
          << a[i].getDoctorId() << "," << a[i].getDate() << ","
          << a[i].getTimeSlot() << "," << a[i].getStatus() << "\n";
    f.close();
}

void FileHandler::saveAllBills(Storage<Bill>& s) {
    ofstream f("bills.txt");
    Bill* a = s.getAll();
    for (int i = 0; i < s.size(); i++)
        f << a[i].getBillId() << "," << a[i].getPatientId() << ","
          << a[i].getAppointmentId() << "," << floatToStr(a[i].getAmount()) << ","
          << a[i].getStatus() << "," << a[i].getDate() << "\n";
    f.close();
}

void FileHandler::saveAllPrescriptions(Storage<Prescription>& s) {
    ofstream f("prescriptions.txt");
    Prescription* a = s.getAll();
    for (int i = 0; i < s.size(); i++)
        f << a[i].getPrescriptionId() << "," << a[i].getAppointmentId() << ","
          << a[i].getPatientId() << "," << a[i].getDoctorId() << ","
          << a[i].getDate() << "," << a[i].getMedicines() << ","
          << a[i].getNotes() << "\n";
    f.close();
}

// ====== Append functions ======

void FileHandler::appendPatient(const Patient& p) {
    ofstream f("patients.txt", ios::app);
    f << p.getId() << "," << p.getName() << "," << p.getAge() << ","
      << p.getGender() << "," << p.getContact() << "," << p.getPassword()
      << "," << floatToStr(p.getBalance()) << "\n";
    f.close();
}

void FileHandler::appendDoctor(const Doctor& d) {
    ofstream f("doctors.txt", ios::app);
    f << d.getId() << "," << d.getName() << "," << d.getSpecialization()
      << "," << d.getContact() << "," << d.getPassword()
      << "," << floatToStr(d.getFee()) << "\n";
    f.close();
}

void FileHandler::appendAppointment(const Appointment& a) {
    ofstream f("appointments.txt", ios::app);
    f << a.getAppointmentId() << "," << a.getPatientId() << ","
      << a.getDoctorId() << "," << a.getDate() << ","
      << a.getTimeSlot() << "," << a.getStatus() << "\n";
    f.close();
}

void FileHandler::appendBill(const Bill& b) {
    ofstream f("bills.txt", ios::app);
    f << b.getBillId() << "," << b.getPatientId() << ","
      << b.getAppointmentId() << "," << floatToStr(b.getAmount()) << ","
      << b.getStatus() << "," << b.getDate() << "\n";
    f.close();
}

void FileHandler::appendPrescription(const Prescription& pr) {
    ofstream f("prescriptions.txt", ios::app);
    f << pr.getPrescriptionId() << "," << pr.getAppointmentId() << ","
      << pr.getPatientId() << "," << pr.getDoctorId() << ","
      << pr.getDate() << "," << pr.getMedicines() << "," << pr.getNotes() << "\n";
    f.close();
}

void FileHandler::logSecurityEvent(const string& role, const string& enteredId, const string& result) {
    ofstream f("security_log.txt", ios::app);
    time_t now = time(0);
    char timeBuf[30];
    strftime(timeBuf, 30, "%d-%m-%Y %H:%M:%S", localtime(&now));
    f << timeBuf << "," << role << "," << enteredId << "," << result << "\n";
    f.close();
}

void FileHandler::readSecurityLog(string& out) {
    out = "";
    ifstream file("security_log.txt");
    if (!file.is_open()) { out = "No security events logged."; return; }
    char line[200];
    while (file.getline(line, 200)) {
        if (line[0] != '\0') { out += line; out += "\n"; }
    }
    if (out.size() == 0) out = "No security events logged.";
    file.close();
}

void FileHandler::archivePatient(const Patient& p, Storage<Appointment>& apps,
                                  Storage<Bill>& bills, Storage<Prescription>& prescs) {
    ofstream f("discharged.txt", ios::app);
    f << p.getId() << "," << p.getName() << "," << p.getAge() << ","
      << p.getGender() << "," << p.getContact() << "," << p.getPassword()
      << "," << floatToStr(p.getBalance()) << "\n";
    Appointment* aa = apps.getAll();
    for (int i = 0; i < apps.size(); i++)
        if (aa[i].getPatientId() == p.getId())
            f << aa[i].getAppointmentId() << "," << aa[i].getPatientId() << ","
              << aa[i].getDoctorId() << "," << aa[i].getDate() << ","
              << aa[i].getTimeSlot() << "," << aa[i].getStatus() << "\n";
    Bill* bb = bills.getAll();
    for (int i = 0; i < bills.size(); i++)
        if (bb[i].getPatientId() == p.getId())
            f << bb[i].getBillId() << "," << bb[i].getPatientId() << ","
              << bb[i].getAppointmentId() << "," << floatToStr(bb[i].getAmount()) << ","
              << bb[i].getStatus() << "," << bb[i].getDate() << "\n";
    Prescription* pp = prescs.getAll();
    for (int i = 0; i < prescs.size(); i++)
        if (pp[i].getPatientId() == p.getId())
            f << pp[i].getPrescriptionId() << "," << pp[i].getAppointmentId() << ","
              << pp[i].getPatientId() << "," << pp[i].getDoctorId() << ","
              << pp[i].getDate() << "," << pp[i].getMedicines() << ","
              << pp[i].getNotes() << "\n";
    f.close();
}
