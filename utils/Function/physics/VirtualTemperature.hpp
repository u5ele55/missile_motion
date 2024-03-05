#pragma once
#include "Function/Function.hpp"

class VirtualTemperature : public Function<double, double>
{
private:
    double tau_0;
public:
    double operator()(double h);
    VirtualTemperature();
};
