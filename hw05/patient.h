#ifndef PATIENT_H
#define PATIENT_H

#include <string>

class Patient {
public:
    Patient(std::string name, double wait, bool isUrgent);
    std::string getName() const;
    double getWaitTime() const;
    bool isUrgent() const;
private:
    std::string patientName;
    double hoursWaited;
    bool urgent;
};

#endif // PATIENT_H
