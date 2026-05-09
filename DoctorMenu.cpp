#include "DoctorMenu.h"

string DoctorMenu::getToday() const {
    time_t n = time(0); char b[15]; strftime(b, 15, "%d-%m-%Y", localtime(&n)); return string(b);
}

int DoctorMenu::getMaxPrescId() {
    int m = 0; Prescription* a = prescriptions->getAll();
    for (int i = 0; i < prescriptions->size(); i++)
        if (a[i].getPrescriptionId() > m) m = a[i].getPrescriptionId();
    return m;
}

string DoctorMenu::buildTodayAppts() {
    string td = getToday(); Appointment* all = appointments->getAll(); int c = 0; Appointment t[100];
    for (int i = 0; i < appointments->size(); i++)
        if (all[i].getDoctorId() == doctor->getId() && all[i].getDate() == td) t[c++] = all[i];
    if (c == 0) return "No appointments today.";
    string r = "Today: " + td + "\n\nApptID | Patient | Time | Status\n------------------------------------\n";
    for (int i = 0; i < c; i++) {
        Patient* p = patients->findById(t[i].getPatientId());
        r += iToS(t[i].getAppointmentId()) + " | " + (p ? p->getName() : "?") + " | " + t[i].getTimeSlot() + " | " + t[i].getStatus() + "\n";
    }
    return r;
}

string DoctorMenu::buildPendingToday() {
    string td = getToday(); Appointment* all = appointments->getAll(); int c = 0;
    string r = "Pending today:\n\nApptID | Patient | Time\n--------------------------\n";
    for (int i = 0; i < appointments->size(); i++) {
        if (all[i].getDoctorId() == doctor->getId() && all[i].getDate() == td && all[i].getStatus() == "pending") {
            Patient* p = patients->findById(all[i].getPatientId());
            r += iToS(all[i].getAppointmentId()) + " | " + (p ? p->getName() : "?") + " | " + all[i].getTimeSlot() + "\n"; c++;
        }
    }
    if (c == 0) return "No pending today.";
    return r;
}

string DoctorMenu::buildPatHist(int pid) {
    Patient* pat = patients->findById(pid);
    if (!pat) return "Patient not found.";
    Appointment* aa = appointments->getAll(); bool hasAny = false;
    for (int i = 0; i < appointments->size(); i++)
        if (aa[i].getPatientId() == pid && aa[i].getDoctorId() == doctor->getId()) { hasAny = true; break; }
    if (!hasAny) return "No appointments found with this patient.";
    string r = "Patient: " + pat->getName() + " | Age: " + iToS(pat->getAge()) + " | Gender: " + pat->getGender() + "\n\n";
    r += "Appointments:\nApptID | Date | Time | Status\n-------------------------------\n";
    for (int i = 0; i < appointments->size(); i++)
        if (aa[i].getPatientId() == pid && aa[i].getDoctorId() == doctor->getId())
            r += iToS(aa[i].getAppointmentId()) + " | " + aa[i].getDate() + " | " + aa[i].getTimeSlot() + " | " + aa[i].getStatus() + "\n";
    Prescription* ap = prescriptions->getAll(); int pc = 0;
    for (int i = 0; i < prescriptions->size(); i++)
        if (ap[i].getPatientId() == pid && ap[i].getDoctorId() == doctor->getId()) pc++;
    if (pc > 0) {
        r += "\nPrescriptions:\nDate | Medicines | Notes\n-----------------------------\n";
        for (int i = 0; i < prescriptions->size(); i++)
            if (ap[i].getPatientId() == pid && ap[i].getDoctorId() == doctor->getId())
                r += ap[i].getDate() + " | " + ap[i].getMedicines() + " | " + ap[i].getNotes() + "\n";
    } else r += "\nNo prescriptions yet.";
    return r;
}

DoctorMenu::DoctorMenu(Doctor* d, Storage<Patient>* p, Storage<Appointment>* a,
                       Storage<Prescription>* pr, Storage<Bill>* b)
    : doctor(d), patients(p), appointments(a), prescriptions(pr), bills(b) {}

void DoctorMenu::run(sf::RenderWindow& w, sf::Font& f) {
    int st = 0; string disp, smsg; float sy = 0; int pAid = 0; string pMeds;
    Button mb[6]; const char* lb[6] = {"Today's Appts","Mark Complete","Mark No-Show","Write Prescription","Patient History","Logout"};
    for (int i = 0; i < 6; i++) mb[i].create(10, 80 + i * 52, 200, 42, lb[i], f, 15);
    mb[5].setColors(sf::Color(180,50,50), sf::Color(220,80,80));
    TextBox ib; ib.create(370, 520, 350, 32, f, 16);
    Button sub; sub.create(740, 518, 90, 36, "Submit", f, 15);
    Button bk; bk.create(840, 518, 80, 36, "Back", f, 15); bk.setColors(sf::Color(120,120,120), sf::Color(160,160,160));
    while (w.isOpen()) {
        while (const auto ev = w.pollEvent()) {
            if (ev->is<sf::Event::Closed>()) { w.close(); return; }
            if (ev->is<sf::Event::MouseButtonPressed>()) {
                ib.handleMouseClick(w);
                if (st == 0) {
                    for (int i = 0; i < 6; i++) {
                        if (mb[i].handleClick(w)) {
                            disp = ""; sy = 0; smsg = ""; ib.clear();
                            if (i == 0) { st = 1; disp = buildTodayAppts(); }
                            else if (i == 1) { st = 10; disp = buildPendingToday() + "\n\nEnter Appt ID:"; }
                            else if (i == 2) { st = 11; disp = buildPendingToday() + "\n\nEnter Appt ID:"; }
                            else if (i == 3) { st = 20; disp = "Enter completed Appt ID:"; }
                            else if (i == 4) { st = 30; disp = "Enter Patient ID:"; }
                            else if (i == 5) return;
                        }
                    }
                }
                if (st != 0 && bk.handleClick(w)) { st = 0; disp = ""; smsg = ""; ib.clear(); sy = 0; }
                if (st != 0 && sub.handleClick(w)) {
                    string tx = ib.getText();
                    if (st == 10) {
                        int ai = ib.toInt(); ib.clear(); string td = getToday();
                        Appointment* al = appointments->getAll(); Appointment* tg = nullptr;
                        for (int i = 0; i < appointments->size(); i++)
                            if (al[i].getAppointmentId() == ai && al[i].getDoctorId() == doctor->getId() && al[i].getStatus() == "pending" && al[i].getDate() == td) { tg = &al[i]; break; }
                        if (!tg) smsg = "Invalid ID.";
                        else { tg->setStatus("completed"); fh.saveAllAppointments(*appointments); disp = "Marked complete."; st = 99; }
                    }
                    else if (st == 11) {
                        int ai = ib.toInt(); ib.clear(); string td = getToday();
                        Appointment* al = appointments->getAll(); Appointment* tg = nullptr;
                        for (int i = 0; i < appointments->size(); i++)
                            if (al[i].getAppointmentId() == ai && al[i].getDoctorId() == doctor->getId() && al[i].getStatus() == "pending" && al[i].getDate() == td) { tg = &al[i]; break; }
                        if (!tg) smsg = "Invalid ID.";
                        else {
                            tg->setStatus("no-show"); fh.saveAllAppointments(*appointments);
                            Bill* ab = bills->getAll();
                            for (int i = 0; i < bills->size(); i++)
                                if (ab[i].getAppointmentId() == ai) { ab[i].setStatus("cancelled"); break; }
                            fh.saveAllBills(*bills); disp = "Marked no-show."; st = 99;
                        }
                    }
                    else if (st == 20) {
                        pAid = ib.toInt(); ib.clear();
                        Appointment* al = appointments->getAll(); Appointment* tg = nullptr;
                        for (int i = 0; i < appointments->size(); i++)
                            if (al[i].getAppointmentId() == pAid && al[i].getDoctorId() == doctor->getId() && al[i].getStatus() == "completed") { tg = &al[i]; break; }
                        if (!tg) smsg = "Invalid/not completed.";
                        else {
                            Prescription* ap = prescriptions->getAll(); bool ex = false;
                            for (int i = 0; i < prescriptions->size(); i++)
                                if (ap[i].getAppointmentId() == pAid) { ex = true; break; }
                            if (ex) smsg = "Prescription exists.";
                            else { disp = "Enter medicines:"; st = 21; }
                        }
                    }
                    else if (st == 21) { pMeds = tx; ib.clear(); disp = "Enter notes:"; st = 22; }
                    else if (st == 22) {
                        string notes = tx; ib.clear(); string td = getToday();
                        Appointment* al = appointments->getAll(); int pid = 0;
                        for (int i = 0; i < appointments->size(); i++)
                            if (al[i].getAppointmentId() == pAid) { pid = al[i].getPatientId(); break; }
                        int ni = getMaxPrescId() + 1;
                        Prescription pr(ni, pAid, pid, doctor->getId(), td, pMeds, notes);
                        prescriptions->add(pr); fh.appendPrescription(pr); disp = "Prescription saved."; st = 99;
                    }
                    else if (st == 30) { int pid = ib.toInt(); ib.clear(); disp = buildPatHist(pid); st = 31; }
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
        for (int i = 0; i < 6; i++) mb[i].updateHover(w); sub.updateHover(w); bk.updateHover(w);
        w.clear(sf::Color(235,238,248)); drawPanel(w, 0, 0, 220, 700, sf::Color(30,75,60));
        sf::Text ti(f, "Doctor Menu", 22); ti.setFillColor(sf::Color::White); ti.setPosition(sf::Vector2f(25, 10)); w.draw(ti);
        string inf = "Dr. " + doctor->getName() + "\n" + doctor->getSpecialization();
        sf::Text ii(f, inf, 13); ii.setFillColor(sf::Color(180,220,200)); ii.setPosition(sf::Vector2f(15, 42)); w.draw(ii);
        for (int i = 0; i < 6; i++) mb[i].draw(w);
        if (st != 0) {
            sf::Text ct(f, disp, 14); ct.setFillColor(sf::Color(20,20,20)); ct.setPosition(sf::Vector2f(240, 20 - sy)); w.draw(ct);
            bool ni = (st >= 10 && st <= 22) || st == 30;
            if (ni) { ib.draw(w); sub.draw(w); } bk.draw(w);
            if (smsg.size() > 0) { sf::Text sm(f, smsg, 15); sm.setFillColor(sf::Color(200,30,30)); sm.setPosition(sf::Vector2f(240, 570)); w.draw(sm); }
        } else {
            sf::Text wl(f, "Select an option.", 18); wl.setFillColor(sf::Color(80,80,80)); wl.setPosition(sf::Vector2f(300, 300)); w.draw(wl);
        }
        w.display();
    }
}
