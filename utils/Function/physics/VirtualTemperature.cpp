#include "VirtualTemperature.hpp"

#include <cmath>

double VirtualTemperature::operator()(double h)
{
    if (h < 9324) {
        return tau_0 - 0.006328 * h;
    } else if (h < 12000) {
        return 230 - 0.006328 * (h - 9324) + 1.172e-6 * pow(h - 9324, 2);
    } else if (h < 30000) {
        return 221.5;
    }
    return 221.5; // ??? 
}

VirtualTemperature::VirtualTemperature() : tau_0(288.9)
{}
