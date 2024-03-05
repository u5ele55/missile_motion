#include "Core.hpp"

#include "utils/file_input/filenames.hpp"
#include "utils/coordinates.hpp"
#include "utils/LinAlg.hpp"

#include "missile_motion/modeling/RK4Solver.hpp"
#include "missile_motion/system/MissileSystem.hpp"

#include "global/GlobalScope.hpp"
#include "global/Constants.hpp"

#include <cmath>
#include <iostream>

Core::Core()
    : model(nullptr),
    solver(nullptr)
{
    ParametersInputter paramsCreator(
        FILENAMES.at("missile"), FILENAMES.at("launch")
    );
    params = paramsCreator.create();

    GlobalScope::getInstance().setParameters(params);
}

Vector Core::calculateEndpoint()
{
    // TODO 
    return {1,1,1};
}

Core::~Core()
{
    delete params;
    delete solver;
    delete model;
}
