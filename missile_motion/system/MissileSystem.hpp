#pragma once
#include "ISystem.hpp"
#include "Parameters.hpp"
#include "utils/Function/Function.hpp"
#include "Function/physics/AtmosphereParameters.hpp"

class MissileSystem : public ISystem
{
private:
    Vector initialState;
    Parameters *params;

    Function<double, AtmosphereParameters> *atmosphere;
    Function<double, double> *virtualTemperature;
    Function<double, double> *axialDumpingMoment;
public:
    MissileSystem(Parameters * params, Vector initialState);
    ~MissileSystem();
    void f(Vector &state, double time) const;
    Vector getInitialState() const;

}; 