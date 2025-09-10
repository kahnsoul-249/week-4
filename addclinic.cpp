#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Lớp Patient (lớp cơ sở)
class Patient {
protected:
    string name;
    int id;
    int age;
public:
    Patient(string n, int i, int a) : name(n), id(i), age(a) {}
    virtual void scheduleAppointment(string date, string reason) {
        cout << "Appointment scheduled for " << name 
             << " on " << date << " (Reason: " << reason << ")\n";
    }
    virtual void displayInfo() {
        cout << "Patient: " << name << ", ID: " << id << ", Age: " << age << endl;
    }
    virtual ~Patient() {} // Destructor ảo để hỗ trợ kế thừa
};

// Lớp ChronicPatient ( lớp bệnh nhân mãn tính )
class ChronicPatient : public Patient {
private:
    string condition;
    string lastCheckup;
public:
    ChronicPatient(string n, int i, int a, string cond, string check)
        : Patient(n, i, a), condition(cond), lastCheckup(check) {}

    void scheduleAppointment(string date, string reason) override {
        cout << "Chronic patient " << name << " (" << condition 
             << ") requires regular follow-up.\n";
        cout << "Appointment scheduled on " << date << " (Reason: " << reason << ")\n";
    }

    void displayInfo() override {
        Patient::displayInfo();
        cout << "Condition: " << condition << ", Last checkup: " << lastCheckup << endl;
    }
};

// Lớp EmergencyPatient (lớp bệnh nhân cấp cứu kế thừa từ Patient, em bổ sung thông tin có tham khảo từ LLM)
class EmergencyPatient : virtual public Patient {
private:
    string emergencyType;
    string admissionDate;
public:
    EmergencyPatient(string n, int i, int a, string eType, string aDate)
        : Patient(n, i, a), emergencyType(eType), admissionDate(aDate) {}

    void scheduleAppointment(string date, string reason) override {
        cout << "Emergency patient " << name << " (" << emergencyType 
             << ") requires urgent attention.\n";
        cout << "Appointment scheduled on " << date << " (Reason: " << reason << ")\n";
    }

    void displayInfo() override {
        Patient::displayInfo();
        cout << "Emergency Type: " << emergencyType << ", Admission Date: " << admissionDate << endl;
    }
};

// Lớp Outpatient (lớp bệnh nhân ngoại trú kế thừa từ Patient, cũng có tham khảo thêm từ LLM)
class Outpatient : virtual public Patient {
private:
    string visitReason;
    string lastVisit;
public:
    Outpatient(string n, int i, int a, string vReason, string lVisit)
        : Patient(n, i, a), visitReason(vReason), lastVisit(lVisit) {}

    void scheduleAppointment(string date, string reason) override {
        cout << "Outpatient " << name << " scheduled for follow-up visit.\n";
        cout << "Appointment scheduled on " << date << " (Reason: " << reason << ")\n";
    }

    void displayInfo() override {
        Patient::displayInfo();
        cout << "Visit Reason: " << visitReason << ", Last Visit: " << lastVisit << endl;
    }
};

// Lớp Doctor
class Doctor {
private:
    string name;
    string specialty;
public:
    Doctor(string n, string s) : name(n), specialty(s) {}
    void displayInfo() {
        cout << "Doctor: " << name << ", Specialty: " << specialty << endl;
    }
};

// Lớp Appointment
class Appointment {
private:
    string date, time, reason, status;
public:
    Appointment(string d, string t, string r) 
        : date(d), time(t), reason(r), status("Scheduled") {}
    void complete() { status = "Completed"; }
    void cancel() { status = "Canceled"; }
    void display() {
        cout << "Appointment: " << date << " " << time 
             << " + " << reason << " + Status: " << status << endl;
    }
};

// Hàm Main
int main() {
    // Tạo bệnh nhân thường
    Patient p1("Tai", 001, 21);
    p1.displayInfo();
    p1.scheduleAppointment("24-09-2025", "General checkup");

    cout << "+\n";

    // Tạo bệnh nhân mãn tính
    ChronicPatient cp1("Bao", 002, 40, "Diabetes", "09-09-2025");
    cp1.displayInfo();
    cp1.scheduleAppointment("25-09-2025", "Cancer");

    cout << "+\n";

    // Tạo bệnh nhân khẩn cấp
    EmergencyPatient ep1("Minh", 003, 55, "Heart Attack", "10-09-2025");
    ep1.displayInfo();
    ep1.scheduleAppointment("15-09-2025", "Emergency Surgery");

    cout << "+\n";

    // Tạo bệnh nhân ngoại trú
    Outpatient op1("Khue", 004, 22, "Stomachache", "11-09-2025");
    op1.displayInfo();
    op1.scheduleAppointment("20-09-2025", "Follow-up Consultation");

    cout << "+\n";

    // Tạo bác sĩ
    Doctor d1("Dr.Xuan Phung", "Cardiology + Internal Medicine");
    d1.displayInfo();

    cout << "+\n";

    // Tạo lịch hẹn
    Appointment a1("25-09-2025", "09:00", "Consultation");
    a1.display();
    a1.complete();
    a1.display();

    return 0;
}