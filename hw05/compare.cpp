#include "compare.h"

Compare::Compare() {}

bool Compare::operator()(const Patient &A, const Patient &B) const
{
    if ((A.isUrgent() && B.isUrgent()) || (!(A.isUrgent()) && !(B.isUrgent())))
        return 12.00 - A.getWaitTime() > 12.00 - B.getWaitTime();
    else if (A.isUrgent())
        return false;
    else if (B.isUrgent())
        return true;
}
