#include "patient.h"

Patient::Patient(std::string name, double wait, bool urgency) :
    patientName(name), hoursWaited(wait), urgent(urgency) {}

std::string Patient::getName() const
{
    return patientName;
}

double Patient::getWaitTime() const
{
    return hoursWaited;
}

bool Patient::isUrgent() const
{
    return urgent;
}
