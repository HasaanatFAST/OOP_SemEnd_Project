#include "AdminMenu.h"

string AdminMenu::getToday() const {
    time_t n = time(0); char b[15]; strftime(b, 15, "%d-%m-%Y", localtime(&n)); return string(b);
}

int AdminMenu::getMaxDocId() {
    int m = 0; Doctor* a = doctors->getAll();
    for (int i = 0; i < doctors->size(); i++) if (a[i].getId() > m) m = a[i].getId();
    return m;
}

string AdminMenu::buildAllPats() {
    Patient* a = patients->getAll(); Bill* ab = bills->getAll();
    if (patients->size() == 0) return "No patients.";
    string r = "ID | Name | Age | Gender | Contact | Balance | Unpaid\n----------------------------------------------------------\n";
    for (int i = 0; i < patients->size(); i++) {
        int uc = 0;
        for (int j = 0; j < bills->size(); j++)
            if (ab[j].getPatientId() == a[i].getId() && ab[j].getStatus() == "unpaid") uc++;
        r += iToS(a[i].getId()) + " | " + a[i].getName() + " | " + iToS(a[i].getAge()) + " | " + a[i].getGender() + " | " + a[i].getContact() + " | " + fToS(a[i].getBalance()) + " | " + iToS(uc) + "\n";
    }
    return r;
}

string AdminMenu::buildAllDocs() {
    Doctor* a = doctors->getAll();
    if (doctors->size() == 0) return "No doctors.";
    string r = "ID | Name | Specialization | Contact | Fee\n--------------------------------------------------\n";
    for (int i = 0; i < doctors->size(); i++)
        r += iToS(a[i].getId()) + " | " + a[i].getName() + " | " + a[i].getSpecialization() + " | " + a[i].getContact() + " | " + fToS(a[i].getFee()) + "\n";
    return r;
}

string AdminMenu::buildAllAppts() {
    Appointment* a = appointments->getAll(); int c = appointments->size();
    if (c == 0) return "No appointments.";
    string r = "ID | Patient | Doctor | Date | Time | Status\n----------------------------------------------------\n";
    for (int i = 0; i < c; i++) {
        Patient* p = patients->findById(a[i].getPatientId());
        Doctor* d = doctors->findById(a[i].getDoctorId());
        r += iToS(a[i].getAppointmentId()) + " | " + (p ? p->getName() : "?") + " | " + (d ? d->getName() : "?") + " | " + a[i].getDate() + " | " + a[i].getTimeSlot() + " | " + a[i].getStatus() + "\n";
    }
    return r;
}

string AdminMenu::buildUnpaid() {
    Bill* a = bills->getAll(); int c = 0;
    string r = "BillID | Patient | Amount | Date\n---------------------------------\n";
    for (int i = 0; i < bills->size(); i++) {
        if (a[i].getStatus() == "unpaid") {
            Patient* p = patients->findById(a[i].getPatientId());
            r += iToS(a[i].getBillId()) + " | " + (p ? p->getName() : "?") + " | " + fToS(a[i].getAmount()) + " | " + a[i].getDate() + "\n"; c++;
        }
    }
    if (c == 0) return "No unpaid bills.";
    return r;
}

string AdminMenu::buildSecLog() {
    string out; fh.readSecurityLog(out); return "Security Log:\n\n" + out;
}

string AdminMenu::buildReport() {
    string td = getToday(); Appointment* aa = appointments->getAll();
    int tot = 0, pen = 0, comp = 0, nos = 0, can = 0;
    for (int i = 0; i < appointments->size(); i++) {
        if (aa[i].getDate() == td) {
            tot++;
            if (aa[i].getStatus() == "pending") pen++;
            else if (aa[i].getStatus() == "completed") comp++;
            else if (aa[i].getStatus() == "no-show") nos++;
            else if (aa[i].getStatus() == "cancelled") can++;
        }
    }
    Bill* ab = bills->getAll(); float rev = 0;
    for (int i = 0; i < bills->size(); i++)
        if (ab[i].getStatus() == "paid" && ab[i].getDate() == td) rev += ab[i].getAmount();
    string r = "Daily Report - " + td + "\n=========================\n\nAppointments: " + iToS(tot) + "\n  Pending: " + iToS(pen)
        + "\n  Completed: " + iToS(comp) + "\n  No-show: " + iToS(nos) + "\n  Cancelled: " + iToS(can)
        + "\n\nRevenue: PKR " + fToS(rev) + "\n";
    Patient* ap = patients->getAll(); r += "\nOutstanding bills:\n";
    for (int i = 0; i < patients->size(); i++) {
        float ow = 0;
        for (int j = 0; j < bills->size(); j++)
            if (ab[j].getPatientId() == ap[i].getId() && ab[j].getStatus() == "unpaid") ow += ab[j].getAmount();
        if (ow > 0) r += "  " + ap[i].getName() + ": PKR " + fToS(ow) + "\n";
    }
    return r;
}

AdminMenu::AdminMenu(Admin* a, Storage<Patient>* p, Storage<Doctor>* d,
                     Storage<Appointment>* ap, Storage<Bill>* b, Storage<Prescription>* pr)
    : admin(a), patients(p), doctors(d), appointments(ap), bills(b), prescriptions(pr) {}

void AdminMenu::run(sf::RenderWindow& w, sf::Font& f) {
    int st = 0; string disp, smsg; float sy = 0; string adNm, adSp, adCt, adPw;
    Button mb[10]; const char* lb[10] = {"Add Doctor","Remove Doctor","All Patients","All Doctors","All Appts","Unpaid Bills","Discharge","Security Log","Daily Report","Logout"};
    for (int i = 0; i < 10; i++) mb[i].create(10, 60 + i * 46, 200, 38, lb[i], f, 14);
    mb[9].setColors(sf::Color(180,50,50), sf::Color(220,80,80));
    TextBox ib; ib.create(370, 520, 300, 32, f, 16);
    Button sub; sub.create(690, 518, 90, 36, "Submit", f, 15);
    Button bk; bk.create(790, 518, 80, 36, "Back", f, 15); bk.setColors(sf::Color(120,120,120), sf::Color(160,160,160));
    while (w.isOpen()) {
        while (const auto ev = w.pollEvent()) {
            if (ev->is<sf::Event::Closed>()) { w.close(); return; }
            if (ev->is<sf::Event::MouseButtonPressed>()) {
                ib.handleMouseClick(w);
                if (st == 0) {
                    for (int i = 0; i < 10; i++) {
                        if (mb[i].handleClick(w)) {
                            disp = ""; sy = 0; smsg = ""; ib.clear();
                            if (i == 0) { st = 10; disp = "Enter doctor name:"; }
                            else if (i == 1) { st = 20; disp = buildAllDocs() + "\n\nEnter Doctor ID:"; }
                            else if (i == 2) { st = 1; disp = buildAllPats(); }
                            else if (i == 3) { st = 2; disp = buildAllDocs(); }
                            else if (i == 4) { st = 3; disp = buildAllAppts(); }
                            else if (i == 5) { st = 4; disp = buildUnpaid(); }
                            else if (i == 6) { st = 30; disp = "Enter Patient ID to discharge:"; }
                            else if (i == 7) { st = 5; disp = buildSecLog(); }
                            else if (i == 8) { st = 6; disp = buildReport(); }
                            else if (i == 9) return;
                        }
                    }
                }
                if (st != 0 && bk.handleClick(w)) { st = 0; disp = ""; smsg = ""; ib.clear(); sy = 0; }
                if (st != 0 && sub.handleClick(w)) {
                    string tx = ib.getText();
                    if (st == 10) { adNm = tx; ib.clear(); disp = "Enter specialization:"; st = 11; }
                    else if (st == 11) { adSp = tx; ib.clear(); disp = "Enter contact (11 digits):"; st = 12; }
                    else if (st == 12) { if (!v.isValidContact(tx)) smsg = "Invalid contact."; else { adCt = tx; ib.clear(); disp = "Enter password (6+):"; st = 13; } }
                    else if (st == 13) { if (!v.isValidPassword(tx)) smsg = "Invalid password."; else { adPw = tx; ib.clear(); disp = "Enter fee:"; st = 14; } }
                    else if (st == 14) {
                        float fee = ib.toFloat(); ib.clear();
                        if (fee <= 0) smsg = "Fee must be > 0.";
                        else {
                            int ni = getMaxDocId() + 1;
                            Doctor d(ni, adNm, adSp, adCt, adPw, fee);
                            doctors->add(d); fh.appendDoctor(d);
                            disp = "Doctor added! ID: " + iToS(ni); st = 99;
                        }
                    }
                    else if (st == 20) {
                        int di = ib.toInt(); ib.clear();
                        Appointment* aa = appointments->getAll(); bool hp = false;
                        for (int i = 0; i < appointments->size(); i++)
                            if (aa[i].getDoctorId() == di && aa[i].getStatus() == "pending") { hp = true; break; }
                        if (hp) smsg = "Has pending appts.";
                        else {
                            bool rm = doctors->removeById(di);
                            if (!rm) smsg = "Not found.";
                            else { fh.saveAllDoctors(*doctors); disp = "Doctor removed."; st = 99; }
                        }
                    }
                    else if (st == 30) {
                        int pi = ib.toInt(); ib.clear();
                        Patient* pt = patients->findById(pi);
                        if (!pt) smsg = "Not found.";
                        else {
                            Bill* ab = bills->getAll(); bool hu = false;
                            for (int i = 0; i < bills->size(); i++)
                                if (ab[i].getPatientId() == pi && ab[i].getStatus() == "unpaid") { hu = true; break; }
                            if (hu) smsg = "Has unpaid bills.";
                            else {
                                Appointment* aa = appointments->getAll(); bool hp = false;
                                for (int i = 0; i < appointments->size(); i++)
                                    if (aa[i].getPatientId() == pi && aa[i].getStatus() == "pending") { hp = true; break; }
                                if (hp) smsg = "Has pending appts.";
                                else {
                                    fh.archivePatient(*pt, *appointments, *bills, *prescriptions);
                                    patients->removeById(pi); fh.saveAllPatients(*patients);
                                    // Clean related records
                                    Appointment* al = appointments->getAll(); Appointment na[100]; int nc = 0;
                                    for (int i = 0; i < appointments->size(); i++)
                                        if (al[i].getPatientId() != pi) na[nc++] = al[i];
                                    appointments->clear(); for (int i = 0; i < nc; i++) appointments->add(na[i]);
                                    fh.saveAllAppointments(*appointments);
                                    Bill* bl = bills->getAll(); Bill nb[100]; int nbc = 0;
                                    for (int i = 0; i < bills->size(); i++)
                                        if (bl[i].getPatientId() != pi) nb[nbc++] = bl[i];
                                    bills->clear(); for (int i = 0; i < nbc; i++) bills->add(nb[i]);
                                    fh.saveAllBills(*bills);
                                    Prescription* pl = prescriptions->getAll(); Prescription np[100]; int npc = 0;
                                    for (int i = 0; i < prescriptions->size(); i++)
                                        if (pl[i].getPatientId() != pi) np[npc++] = pl[i];
                                    prescriptions->clear(); for (int i = 0; i < npc; i++) prescriptions->add(np[i]);
                                    fh.saveAllPrescriptions(*prescriptions);
                                    disp = "Patient discharged."; st = 99;
                                }
                            }
                        }
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
        for (int i = 0; i < 10; i++) mb[i].updateHover(w); sub.updateHover(w); bk.updateHover(w);
        w.clear(sf::Color(235,238,248)); drawPanel(w, 0, 0, 220, 700, sf::Color(90,40,40));
        sf::Text ti(f, "Admin Panel", 22); ti.setFillColor(sf::Color::White); ti.setPosition(sf::Vector2f(35, 15)); w.draw(ti);
        for (int i = 0; i < 10; i++) mb[i].draw(w);
        if (st != 0) {
            sf::Text ct(f, disp, 14); ct.setFillColor(sf::Color(20,20,20)); ct.setPosition(sf::Vector2f(240, 20 - sy)); w.draw(ct);
            bool ni = (st >= 10 && st <= 14) || st == 20 || st == 30;
            if (ni) { ib.draw(w); sub.draw(w); } bk.draw(w);
            if (smsg.size() > 0) { sf::Text sm(f, smsg, 15); sm.setFillColor(sf::Color(200,30,30)); sm.setPosition(sf::Vector2f(240, 570)); w.draw(sm); }
        } else {
            sf::Text wl(f, "Select an option.", 18); wl.setFillColor(sf::Color(80,80,80)); wl.setPosition(sf::Vector2f(300, 300)); w.draw(wl);
        }
        w.display();
    }
}
