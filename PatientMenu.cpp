#include "PatientMenu.h"

string PatientMenu::getTodayDate() const {
    time_t n = time(0); char b[15]; strftime(b, 15, "%d-%m-%Y", localtime(&n)); return string(b);
}

int PatientMenu::getCurrentYear() const {
    time_t n = time(0); return localtime(&n)->tm_year + 1900;
}

int PatientMenu::getMaxApptId() {
    int m = 0; Appointment* a = appointments->getAll();
    for (int i = 0; i < appointments->size(); i++)
        if (a[i].getAppointmentId() > m) m = a[i].getAppointmentId();
    return m;
}

int PatientMenu::getMaxBillId() {
    int m = 0; Bill* b = bills->getAll();
    for (int i = 0; i < bills->size(); i++)
        if (b[i].getBillId() > m) m = b[i].getBillId();
    return m;
}

int PatientMenu::cmpDates(const string& a, const string& b) const {
    for (int i = 6; i <= 9; i++) { if (a[i] < b[i]) return -1; if (a[i] > b[i]) return 1; }
    for (int i = 3; i <= 4; i++) { if (a[i] < b[i]) return -1; if (a[i] > b[i]) return 1; }
    for (int i = 0; i <= 1; i++) { if (a[i] < b[i]) return -1; if (a[i] > b[i]) return 1; }
    return 0;
}

string PatientMenu::buildApptList() {
    Appointment* all = appointments->getAll(); int c = 0; Appointment t[100];
    for (int i = 0; i < appointments->size(); i++)
        if (all[i].getPatientId() == patient->getId()) t[c++] = all[i];
    if (c == 0) return "No appointments.";
    for (int i = 0; i < c - 1; i++)
        for (int j = 0; j < c - 1 - i; j++)
            if (cmpDates(t[j].getDate(), t[j + 1].getDate()) > 0) { Appointment x = t[j]; t[j] = t[j + 1]; t[j + 1] = x; }
    string r = "ID | Doctor | Date | Time | Status\n------------------------------------------\n";
    for (int i = 0; i < c; i++) {
        Doctor* d = doctors->findById(t[i].getDoctorId());
        r += iToS(t[i].getAppointmentId()) + " | " + (d ? d->getName() : "?") + " | " + t[i].getDate() + " | " + t[i].getTimeSlot() + " | " + t[i].getStatus() + "\n";
    }
    return r;
}

string PatientMenu::buildMedRecords() {
    Prescription* all = prescriptions->getAll(); int c = 0; Prescription t[100];
    for (int i = 0; i < prescriptions->size(); i++)
        if (all[i].getPatientId() == patient->getId()) t[c++] = all[i];
    if (c == 0) return "No medical records.";
    string r = "Date | Doctor | Medicines | Notes\n--------------------------------------\n";
    for (int i = 0; i < c; i++) {
        Doctor* d = doctors->findById(t[i].getDoctorId());
        r += t[i].getDate() + " | " + (d ? d->getName() : "?") + " | " + t[i].getMedicines() + " | " + t[i].getNotes() + "\n";
    }
    return r;
}

string PatientMenu::buildBillList() {
    Bill* all = bills->getAll(); float tot = 0; bool f = false;
    string r = "BillID | ApptID | Amount | Status | Date\n-------------------------------------------\n";
    for (int i = 0; i < bills->size(); i++) {
        if (all[i].getPatientId() == patient->getId()) {
            r += iToS(all[i].getBillId()) + " | " + iToS(all[i].getAppointmentId()) + " | " + fToS(all[i].getAmount()) + " | " + all[i].getStatus() + " | " + all[i].getDate() + "\n";
            if (all[i].getStatus() == "unpaid") tot += all[i].getAmount(); f = true;
        }
    }
    if (!f) return "No bills.";
    r += "\nTotal Owed: PKR " + fToS(tot);
    return r;
}

string PatientMenu::buildDocsBySpec(const string& sp) {
    Doctor* all = doctors->getAll(); int c = 0;
    string r = "Doctors for '" + sp + "':\n\nID | Name | Fee\n--------------------\n";
    for (int i = 0; i < doctors->size(); i++) {
        if (v.strEqIgnoreCase(all[i].getSpecialization(), sp)) {
            r += iToS(all[i].getId()) + " | " + all[i].getName() + " | " + fToS(all[i].getFee()) + "\n"; c++;
        }
    }
    if (c == 0) return "No doctors found.";
    return r;
}

string PatientMenu::buildSlots(int did, const string& dt) {
    const char* sl[8] = {"09:00","10:00","11:00","12:00","13:00","14:00","15:00","16:00"};
    Appointment* all = appointments->getAll(); string r = "Slots on " + dt + ":\n\n"; int c = 0;
    for (int s = 0; s < 8; s++) {
        bool tk = false;
        for (int i = 0; i < appointments->size(); i++)
            if (all[i].getDoctorId() == did && all[i].getDate() == dt && all[i].getTimeSlot() == sl[s] && all[i].getStatus() != "cancelled") { tk = true; break; }
        if (!tk) { r += "  "; r += sl[s]; r += "\n"; c++; }
    }
    if (c == 0) return "No slots available.";
    return r;
}

string PatientMenu::buildPending() {
    Appointment* all = appointments->getAll(); int c = 0;
    string r = "Pending:\n\nApptID | Doctor | Date | Time\n-------------------------------\n";
    for (int i = 0; i < appointments->size(); i++) {
        if (all[i].getPatientId() == patient->getId() && all[i].getStatus() == "pending") {
            Doctor* d = doctors->findById(all[i].getDoctorId());
            r += iToS(all[i].getAppointmentId()) + " | " + (d ? d->getName() : "?") + " | " + all[i].getDate() + " | " + all[i].getTimeSlot() + "\n"; c++;
        }
    }
    if (c == 0) return "No pending appointments.";
    return r;
}

string PatientMenu::buildUnpaid() {
    Bill* all = bills->getAll(); int c = 0;
    string r = "Unpaid bills:\n\nBillID | Amount | Date\n------------------------\n";
    for (int i = 0; i < bills->size(); i++) {
        if (all[i].getPatientId() == patient->getId() && all[i].getStatus() == "unpaid") {
            r += iToS(all[i].getBillId()) + " | " + fToS(all[i].getAmount()) + " | " + all[i].getDate() + "\n"; c++;
        }
    }
    if (c == 0) return "No unpaid bills.";
    return r;
}

PatientMenu::PatientMenu(Patient* p, Storage<Doctor>* d, Storage<Appointment>* a,
                         Storage<Bill>* b, Storage<Prescription>* pr)
    : patient(p), doctors(d), appointments(a), bills(b), prescriptions(pr) {}

void PatientMenu::run(Storage<Patient>& ps, sf::RenderWindow& w, sf::Font& f) {
    int st = 0; string disp, smsg; float sy = 0; int bDocId = 0; string bDate, bSpec;
    Button mb[8]; const char* lb[8] = {"Book Appt","Cancel Appt","View Appts","Med Records","View Bills","Pay Bill","Top Up","Logout"};
    for (int i = 0; i < 8; i++) mb[i].create(10, 80 + i * 52, 200, 42, lb[i], f, 15);
    mb[7].setColors(sf::Color(180,50,50), sf::Color(220,80,80));
    TextBox ib; ib.create(370, 520, 250, 32, f, 16);
    Button sub; sub.create(640, 518, 90, 36, "Submit", f, 15);
    Button bk; bk.create(740, 518, 80, 36, "Back", f, 15); bk.setColors(sf::Color(120,120,120), sf::Color(160,160,160));
    while (w.isOpen()) {
        while (const auto ev = w.pollEvent()) {
            if (ev->is<sf::Event::Closed>()) { w.close(); return; }
            if (ev->is<sf::Event::MouseButtonPressed>()) {
                ib.handleMouseClick(w);
                if (st == 0) {
                    for (int i = 0; i < 8; i++) {
                        if (mb[i].handleClick(w)) {
                            disp = ""; sy = 0; smsg = ""; ib.clear();
                            if (i == 0) { st = 10; disp = "Enter specialization:"; }
                            else if (i == 1) { st = 20; disp = buildPending() + "\n\nEnter Appt ID:"; }
                            else if (i == 2) { st = 1; disp = buildApptList(); }
                            else if (i == 3) { st = 2; disp = buildMedRecords(); }
                            else if (i == 4) { st = 3; disp = buildBillList(); }
                            else if (i == 5) { st = 30; disp = buildUnpaid() + "\n\nEnter Bill ID:"; }
                            else if (i == 6) { st = 40; disp = "Enter amount (PKR):"; }
                            else if (i == 7) return;
                        }
                    }
                }
                if (st != 0 && bk.handleClick(w)) { st = 0; disp = ""; smsg = ""; ib.clear(); sy = 0; }
                if (st != 0 && sub.handleClick(w)) {
                    string tx = ib.getText();
                    if (st == 10) {
                        bSpec = tx; ib.clear(); disp = buildDocsBySpec(bSpec);
                        if (disp.size() > 30) { disp += "\n\nEnter Doctor ID:"; st = 11; }
                        else { smsg = "No doctors."; st = 99; disp = smsg; }
                    }
                    else if (st == 11) {
                        bDocId = ib.toInt(); ib.clear();
                        if (!doctors->findById(bDocId)) smsg = "Doctor not found.";
                        else { disp = "Enter date (DD-MM-YYYY):"; st = 12; }
                    }
                    else if (st == 12) {
                        bDate = tx; ib.clear();
                        if (!v.isValidDate(bDate, getCurrentYear())) smsg = "Invalid date.";
                        else { disp = buildSlots(bDocId, bDate) + "\n\nEnter slot:"; st = 13; }
                    }
                    else if (st == 13) {
                        string sl = tx; ib.clear();
                        if (!v.isValidTimeSlot(sl)) smsg = "Invalid slot.";
                        else {
                            Appointment* al = appointments->getAll(); bool tk = false;
                            for (int i = 0; i < appointments->size(); i++)
                                if (al[i].getDoctorId() == bDocId && al[i].getDate() == bDate && al[i].getTimeSlot() == sl && al[i].getStatus() != "cancelled") { tk = true; break; }
                            if (tk) smsg = "Slot taken!";
                            else {
                                Doctor* dc = doctors->findById(bDocId);
                                if (patient->getBalance() < dc->getFee()) smsg = "Low balance!";
                                else {
                                    *patient -= dc->getFee(); int ai = getMaxApptId() + 1; string td = getTodayDate();
                                    Appointment na(ai, patient->getId(), bDocId, bDate, sl, "pending");
                                    appointments->add(na); fh.appendAppointment(na);
                                    int bi = getMaxBillId() + 1;
                                    Bill nb(bi, patient->getId(), ai, dc->getFee(), "unpaid", td);
                                    bills->add(nb); fh.appendBill(nb); fh.saveAllPatients(ps);
                                    disp = "Booked! ID:" + iToS(ai) + "\nFee:" + fToS(dc->getFee()) + "\nBal:" + fToS(patient->getBalance()); st = 99;
                                }
                            }
                        }
                    }
                    else if (st == 20) {
                        int ai = ib.toInt(); ib.clear();
                        Appointment* al = appointments->getAll(); Appointment* tg = nullptr;
                        for (int i = 0; i < appointments->size(); i++)
                            if (al[i].getAppointmentId() == ai && al[i].getPatientId() == patient->getId() && al[i].getStatus() == "pending") { tg = &al[i]; break; }
                        if (!tg) smsg = "Invalid ID.";
                        else {
                            Doctor* dc = doctors->findById(tg->getDoctorId()); float rf = dc ? dc->getFee() : 0;
                            tg->setStatus("cancelled"); fh.saveAllAppointments(*appointments);
                            *patient += rf; fh.saveAllPatients(ps);
                            Bill* ab = bills->getAll();
                            for (int i = 0; i < bills->size(); i++)
                                if (ab[i].getAppointmentId() == ai) { ab[i].setStatus("cancelled"); break; }
                            fh.saveAllBills(*bills);
                            disp = "Cancelled. Refund:" + fToS(rf) + "\nBal:" + fToS(patient->getBalance()); st = 99;
                        }
                    }
                    else if (st == 30) {
                        int bi = ib.toInt(); ib.clear();
                        Bill* al = bills->getAll(); Bill* tg = nullptr;
                        for (int i = 0; i < bills->size(); i++)
                            if (al[i].getBillId() == bi && al[i].getPatientId() == patient->getId() && al[i].getStatus() == "unpaid") { tg = &al[i]; break; }
                        if (!tg) smsg = "Invalid bill.";
                        else if (patient->getBalance() < tg->getAmount()) smsg = "Low balance!";
                        else {
                            *patient -= tg->getAmount(); tg->setStatus("paid");
                            fh.saveAllBills(*bills); fh.saveAllPatients(ps);
                            disp = "Paid! Bal:" + fToS(patient->getBalance()); st = 99;
                        }
                    }
                    else if (st == 40) {
                        float am = ib.toFloat(); ib.clear();
                        if (am <= 0) smsg = "Must be > 0.";
                        else { *patient += am; fh.saveAllPatients(ps); disp = "Added! Bal:" + fToS(patient->getBalance()); st = 99; }
                    }
                }
            }
            if (ev->is<sf::Event::TextEntered>()) {
                auto* te = ev->getIf<sf::Event::TextEntered>(); if (te) ib.handleTextInput(te->unicode);
            }
            if (ev->is<sf::Event::MouseWheelScrolled>()) {
                auto* ws = ev->getIf<sf::Event::MouseWheelScrolled>();
                if (ws) { sy -= ws->delta * 20; if (sy < 0) sy = 0; }
            }
        }
        for (int i = 0; i < 8; i++) mb[i].updateHover(w); sub.updateHover(w); bk.updateHover(w);
        w.clear(sf::Color(235,238,248)); drawPanel(w, 0, 0, 220, 700, sf::Color(45,55,100));
        sf::Text ti(f, "Patient Menu", 22); ti.setFillColor(sf::Color::White); ti.setPosition(sf::Vector2f(20, 10)); w.draw(ti);
        string inf = patient->getName() + " | PKR " + fToS(patient->getBalance());
        sf::Text ii(f, inf, 14); ii.setFillColor(sf::Color(200,210,255)); ii.setPosition(sf::Vector2f(15, 42)); w.draw(ii);
        for (int i = 0; i < 8; i++) mb[i].draw(w);
        if (st != 0) {
            sf::Text ct(f, disp, 14); ct.setFillColor(sf::Color(20,20,20)); ct.setPosition(sf::Vector2f(240, 20 - sy)); w.draw(ct);
            bool ni = (st >= 10 && st <= 13) || st == 20 || st == 30 || st == 40;
            if (ni) { ib.draw(w); sub.draw(w); } bk.draw(w);
            if (smsg.size() > 0) { sf::Text sm(f, smsg, 15); sm.setFillColor(sf::Color(200,30,30)); sm.setPosition(sf::Vector2f(240, 570)); w.draw(sm); }
        } else {
            sf::Text wl(f, "Select an option.", 18); wl.setFillColor(sf::Color(80,80,80)); wl.setPosition(sf::Vector2f(300, 300)); w.draw(wl);
        }
        w.display();
    }
}
