#ifndef SERIAL_H
#define SERIAL_H

#include "Catheter.h"
#include <Arduino.h>

using Catheter::FourPull;

namespace AscendSerial
{
class CatheterSerial
{
private:
    FourPull activeCatheter;

public:
    CatheterSerial();
    CatheterSerial(FourPull);

    void sendStepsPassed();
    void requestInputString();
    String getInputString();
};
} // namespace AscendSerial
#endif
