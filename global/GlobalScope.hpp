#pragma once

#include "Function/Function.hpp"
#include "Function/physics/AtmosphereParameters.hpp"
#include "FunctionCreator.hpp"
#include "missile_motion/system/Parameters.hpp"

class GlobalScope {
private:
    GlobalScope();
    FunctionCreator creator;
    
    Function<double, AtmosphereParameters> *atmosphere;
    Function<double, double> *axialDumpingMoment;

    Parameters * params;
public:
    GlobalScope(GlobalScope const&)    = delete;
    void operator=(GlobalScope const&) = delete;
    static GlobalScope& getInstance();
    ~GlobalScope();

    Function<double, AtmosphereParameters>* getAtmosphereParamsEvaluator();
    Function<double, double>* getAxialDumpingMomentEvaluator();

    void setParameters(Parameters * params);
};