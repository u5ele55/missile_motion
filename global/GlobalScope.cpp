#include "GlobalScope.hpp"
#include "file_input/filenames.hpp"

#include <stdexcept>

GlobalScope::GlobalScope() 
:   atmosphere(nullptr)
{}

GlobalScope& GlobalScope::getInstance()
{
    static GlobalScope instance;
    return instance;
}

Function<double, AtmosphereParameters> &GlobalScope::getAtmosphereParamsEvaluator()
{
    if (atmosphere == nullptr) {
        atmosphere = new StandartAtmosphereParameters;
    }

    return *atmosphere;
}


void GlobalScope::setParameters(Parameters *params)
{
    this->params = params;
}

GlobalScope::~GlobalScope()
{
    delete atmosphere;
}
