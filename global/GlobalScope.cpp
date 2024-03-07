#include "GlobalScope.hpp"
#include "file_input/filenames.hpp"

#include <stdexcept>

GlobalScope::GlobalScope() 
:   atmosphere(nullptr),
    axialDumpingMoment(nullptr),
    Cx(nullptr),
    Knm(nullptr)
{}

GlobalScope& GlobalScope::getInstance()
{
    static GlobalScope instance;
    return instance;
}

Function<double, AtmosphereParameters> *GlobalScope::getAtmosphereParamsEvaluator()
{
    if (atmosphere == nullptr) {
        atmosphere = new StandartAtmosphereParameters;
    }

    return atmosphere;
}

Function<double, double> *GlobalScope::getAxialDumpingMomentEvaluator()
{
    if (axialDumpingMoment == nullptr) {
        axialDumpingMoment = creator.createLinearInterpolator(FILENAMES.at("axial_dumping_moment"), true);
    }
    return axialDumpingMoment;
}

Function<double, double> *GlobalScope::getCxEvaluator()
{
    if (Cx == nullptr) {
        Cx = creator.createConditionalPolynom(FILENAMES.at("C_x"));
    }
    return Cx;
}

Function<double, double> *GlobalScope::getKnmEvaluator()
{
    if (Knm == nullptr) {
        Knm = creator.createConditionalPolynom(FILENAMES.at("K_nm"));
    }
    return Knm;
}

void GlobalScope::setParameters(Parameters *params)
{
    this->params = params;
}

GlobalScope::~GlobalScope()
{
    delete atmosphere;
}
