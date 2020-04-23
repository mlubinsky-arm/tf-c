#include "mbed.h"
//#include "get_temp.h"

AnalogIn thermOut(P10_1);

float get_temp()
{
    float refVoltage = thermOut.read() * 2.4; // Range of ADC 0->2*Vref
    float refCurrent = refVoltage  / 10000.0; // 10k Reference Resistor
    float thermVoltage = 3.3 - refVoltage;    // Assume supply voltage is 3.3v
    float thermResistance = thermVoltage / refCurrent;
    float logrT = (float32_t)log((float64_t)thermResistance);

    /* Calculate temperature from the resistance of thermistor using Steinhart-Hart Equation */
    float stEqn = (float32_t)((0.0009032679) + ((0.000248772) * logrT) +
                             ((2.041094E-07) * pow((float64)logrT, (float32)3)));

    float temperatureC = (float32_t)(((1.0 / stEqn) - 273.15)  + 0.5);
    return temperatureC;
}
