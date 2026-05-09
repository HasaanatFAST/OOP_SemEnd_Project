#include <SFML/Graphics.hpp>
#include "GUI.h"
#include <iostream>
#include <string>
#include "Patient.h"
#include "Doctor.h"
#include "Admin.h"
#include "Appointment.h"
#include "Bill.h"
#include "Prescription.h"
#include "Storage.h"
#include "FileHandler.h"
#include "Validator.h"
#include "HospitalException.h"
#include "PatientMenu.h"
#include "DoctorMenu.h"
#include "AdminMenu.h"

using namespace std;

// Global storage objects
Storage<Patient> patients;
Storage<Doctor> doctors;
Storage<Appointment> appointments;
Storage<Bill> bills;
Storage<Prescription> prescriptions;
Admin admin;
FileHandler fh;
Validator v;

// Find the highest patient ID currently in use
int getMaxPatientId() {
    int m = 0;
    Patient* a = patients.getAll();
    for (int i = 0; i < patients.size(); i++) {
        if (a[i].getId() > m) {
            m = a[i].getId();
        }
    }
    return m;
}

// Load all data from files at startup
void loadAllData() {
    try {
        fh.loadAdmin(admin);
    }
    catch (FileNotFoundException& e) {
        cout << "Error: " << e.what() << endl;
        exit(1);
    }

    fh.loadPatients(patients);
    fh.loadDoctors(doctors);
    fh.loadAppointments(appointments);
    fh.loadBills(bills);
    fh.loadPrescriptions(prescriptions);
}

int main() {
    loadAllData();

    sf::RenderWindow window(sf::VideoMode({1000, 700}), "MediCore Hospital Management System");
    sf::Font font;

    if (!font.openFromFile("arial.ttf")) {
        cout << "Error: arial.ttf not found." << endl;
        return 1;
    }

    // ---- Main menu title ----
    sf::Text titleText(font, "MediCore Hospital", 36);
    titleText.setFillColor(sf::Color(30, 40, 100));
    sf::FloatRect tb = titleText.getLocalBounds();
    titleText.setPosition(sf::Vector2f(500 - tb.size.x / 2, 60));

    sf::Text subText(font, "Management System", 20);
    subText.setFillColor(sf::Color(80, 90, 140));
    sf::FloatRect sb = subText.getLocalBounds();
    subText.setPosition(sf::Vector2f(500 - sb.size.x / 2, 110));

    // ---- Main menu buttons ----
    Button btnP, btnD, btnA, btnE;
    btnP.create(400, 200, 200, 50, "Patient Login", font, 18);
    btnD.create(400, 270, 200, 50, "Doctor Login", font, 18);
    btnA.create(400, 340, 200, 50, "Admin Login", font, 18);
    btnE.create(400, 430, 200, 50, "Exit", font, 18);
    btnE.setColors(sf::Color(180, 50, 50), sf::Color(220, 80, 80));

    // ---- Login screen ----
    sf::Text loginTitle(font, "Login", 28);
    loginTitle.setFillColor(sf::Color(30, 40, 100));

    sf::Text idLbl(font, "ID:", 18);
    idLbl.setFillColor(sf::Color::Black);
    idLbl.setPosition(sf::Vector2f(310, 232));

    TextBox idBox;
    idBox.create(400, 225, 220, 35, font, 18);

    sf::Text pwLbl(font, "Password:", 18);
    pwLbl.setFillColor(sf::Color::Black);
    pwLbl.setPosition(sf::Vector2f(310, 287));

    TextBox pwBox;
    pwBox.create(400, 280, 220, 35, font, 18);

    Button btnL, btnB;
    btnL.create(400, 340, 100, 40, "Login", font, 16);
    btnB.create(520, 340, 100, 40, "Back", font, 16);
    btnB.setColors(sf::Color(120, 120, 120), sf::Color(160, 160, 160));

    Button btnR;
    btnR.create(400, 400, 220, 40, "New? Register", font, 16);
    btnR.setColors(sf::Color(50, 140, 80), sf::Color(70, 170, 100));

    // ---- Registration screen ----
    sf::Text rLbl[5] = {
        sf::Text(font, "Name:", 16),
        sf::Text(font, "Age:", 16),
        sf::Text(font, "Gender(M/F):", 16),
        sf::Text(font, "Contact(11):", 16),
        sf::Text(font, "Password(6+):", 16)
    };

    TextBox rBox[5];
    for (int i = 0; i < 5; i++) {
        rLbl[i].setFillColor(sf::Color::Black);
        rLbl[i].setPosition(sf::Vector2f(300, 180 + i * 50));
        rBox[i].create(440, 175 + i * 50, 220, 32, font, 16);
    }

    Button btnRS;
    btnRS.create(440, 440, 100, 38, "Register", font, 15);

    Button btnRB;
    btnRB.create(560, 440, 100, 38, "Back", font, 15);
    btnRB.setColors(sf::Color(120, 120, 120), sf::Color(160, 160, 160));

    sf::Text errMsg(font, "", 16);
    errMsg.setFillColor(sf::Color(200, 30, 30));
    errMsg.setPosition(sf::Vector2f(300, 500));

    // 0 = menu, 1 = patLogin, 2 = docLogin, 3 = admLogin, 4 = register
    int state = 0;

    // ---- Main loop ----
    while (window.isOpen()) {
        while (const auto ev = window.pollEvent()) {

            if (ev->is<sf::Event::Closed>()) {
                window.close();
            }

            // ---- Mouse click events ----
            if (ev->is<sf::Event::MouseButtonPressed>()) {

                if (state >= 1 && state <= 3) {
                    idBox.handleMouseClick(window);
                    pwBox.handleMouseClick(window);
                }

                if (state == 4) {
                    for (int i = 0; i < 5; i++) {
                        rBox[i].handleMouseClick(window);
                    }
                }

                // Main menu
                if (state == 0) {
                    if (btnP.handleClick(window)) {
                        state = 1;
                        idBox.clear();
                        pwBox.clear();
                        errMsg.setString("");
                    }
                    if (btnD.handleClick(window)) {
                        state = 2;
                        idBox.clear();
                        pwBox.clear();
                        errMsg.setString("");
                    }
                    if (btnA.handleClick(window)) {
                        state = 3;
                        idBox.clear();
                        pwBox.clear();
                        errMsg.setString("");
                    }
                    if (btnE.handleClick(window)) {
                        window.close();
                    }
                }
                // Login screens
                else if (state >= 1 && state <= 3) {
                    if (btnB.handleClick(window)) {
                        state = 0;
                        errMsg.setString("");
                    }

                    if (state == 1 && btnR.handleClick(window)) {
                        state = 4;
                        errMsg.setString("");
                        for (int i = 0; i < 5; i++) {
                            rBox[i].clear();
                        }
                    }

                    if (btnL.handleClick(window)) {
                        int id = idBox.toInt();
                        string pw = pwBox.getText();
                        bool ok = false;

                        if (state == 1) {
                            Patient* p = patients.findById(id);
                            if (p && p->getPassword() == pw) {
                                PatientMenu m(p, &doctors, &appointments, &bills, &prescriptions);
                                m.run(patients, window, font);
                                state = 0;
                                ok = true;
                            }
                        }
                        else if (state == 2) {
                            Doctor* d = doctors.findById(id);
                            if (d && d->getPassword() == pw) {
                                DoctorMenu m(d, &patients, &appointments, &prescriptions, &bills);
                                m.run(window, font);
                                state = 0;
                                ok = true;
                            }
                        }
                        else if (state == 3) {
                            if (admin.getId() == id && admin.getPassword() == pw) {
                                AdminMenu m(&admin, &patients, &doctors, &appointments, &bills, &prescriptions);
                                m.run(window, font);
                                state = 0;
                                ok = true;
                            }
                        }

                        if (!ok) {
                            errMsg.setString("Invalid ID or Password!");
                            string is = iToS(id);
                            if (state == 1)
                                fh.logSecurityEvent("Patient", is, "FAILED");
                            else if (state == 2)
                                fh.logSecurityEvent("Doctor", is, "FAILED");
                            else if (state == 3)
                                fh.logSecurityEvent("Admin", is, "FAILED");
                        }
                    }
                }
                // Registration screen
                else if (state == 4) {
                    if (btnRB.handleClick(window)) {
                        state = 1;
                        errMsg.setString("");
                    }

                    if (btnRS.handleClick(window)) {
                        string nm = rBox[0].getText();
                        int age = rBox[1].toInt();
                        string gn = rBox[2].getText();
                        string ct = rBox[3].getText();
                        string pw = rBox[4].getText();

                        if (nm.size() == 0)
                            errMsg.setString("Name empty.");
                        else if (age <= 0 || age > 150)
                            errMsg.setString("Invalid age.");
                        else if (gn != "M" && gn != "F" && gn != "m" && gn != "f")
                            errMsg.setString("Gender: M or F.");
                        else if (!v.isValidContact(ct))
                            errMsg.setString("Contact: 11 digits.");
                        else if (!v.isValidPassword(pw))
                            errMsg.setString("Password: 6+ chars.");
                        else {
                            int ni = getMaxPatientId() + 1;
                            Patient np(ni, nm, age, gn, ct, pw, 0.0f);
                            patients.add(np);
                            fh.appendPatient(np);
                            errMsg.setFillColor(sf::Color(20, 130, 50));
                            errMsg.setString("Registered! ID: " + iToS(ni));
                            state = 1;
                            idBox.clear();
                            pwBox.clear();
                        }
                    }
                }
            }

            // ---- Text input events ----
            if (ev->is<sf::Event::TextEntered>()) {
                auto* te = ev->getIf<sf::Event::TextEntered>();
                if (te) {
                    if (state >= 1 && state <= 3) {
                        idBox.handleTextInput(te->unicode);
                        pwBox.handleTextInput(te->unicode);
                    }
                    if (state == 4) {
                        for (int i = 0; i < 5; i++) {
                            rBox[i].handleTextInput(te->unicode);
                        }
                    }
                }
            }
        }

        // ---- Hover updates ----
        if (state == 0) {
            btnP.updateHover(window);
            btnD.updateHover(window);
            btnA.updateHover(window);
            btnE.updateHover(window);
        }
        if (state >= 1 && state <= 3) {
            btnL.updateHover(window);
            btnB.updateHover(window);
            if (state == 1)
                btnR.updateHover(window);
        }
        if (state == 4) {
            btnRS.updateHover(window);
            btnRB.updateHover(window);
        }

        // ---- Drawing ----
        window.clear(sf::Color(235, 238, 248));

        if (state == 0) {
            drawPanel(window, 300, 40, 400, 480, sf::Color(245, 248, 255));
            window.draw(titleText);
            window.draw(subText);
            btnP.draw(window);
            btnD.draw(window);
            btnA.draw(window);
            btnE.draw(window);
        }
        else if (state >= 1 && state <= 3) {
            drawPanel(window, 250, 120, 500, 420, sf::Color(245, 248, 255));

            const char* titles[3] = {"Patient Login", "Doctor Login", "Admin Login"};
            loginTitle.setString(titles[state - 1]);
            sf::FloatRect lt = loginTitle.getLocalBounds();
            loginTitle.setPosition(sf::Vector2f(500 - lt.size.x / 2, 140));

            window.draw(loginTitle);
            window.draw(idLbl);
            idBox.draw(window);
            window.draw(pwLbl);
            pwBox.draw(window);
            btnL.draw(window);
            btnB.draw(window);
            window.draw(errMsg);

            if (state == 1)
                btnR.draw(window);
        }
        else if (state == 4) {
            drawPanel(window, 250, 120, 500, 420, sf::Color(245, 248, 255));

            sf::Text rt(font, "Patient Registration", 26);
            rt.setFillColor(sf::Color(30, 40, 100));
            sf::FloatRect rtb = rt.getLocalBounds();
            rt.setPosition(sf::Vector2f(500 - rtb.size.x / 2, 135));
            window.draw(rt);

            for (int i = 0; i < 5; i++) {
                window.draw(rLbl[i]);
                rBox[i].draw(window);
            }
            btnRS.draw(window);
            btnRB.draw(window);
            window.draw(errMsg);
        }

        window.display();
    }

    return 0;
}
