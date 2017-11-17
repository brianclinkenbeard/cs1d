#ifndef COMPARE_H
#define COMPARE_H

#include "patient.h"

class Compare
{
public:
    Compare();
    bool operator()(const Patient &A, const Patient &B) const;
};

#endif // COMPARE_H
