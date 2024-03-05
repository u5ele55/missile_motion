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
    model = new MissileSystem(params, {
        params->launch.velocity,
        params->launch.elevationAngle,
        params->launch.headingAngle,
        0,
        Constants::Earth::MINOR_AXIS + 1,
        0,
        params->launch.axialAngularVelocity,
        (*GlobalScope::getInstance().getAtmosphereParamsEvaluator())(0).pressure
    });
    solver = new RK4Solver(model, params->modeling.integrationStep);

    for(int i = 0; i < 100; i ++) {
        std::cout << i << " " << solver->solve(i) << '\n';
    }
}

Core::~Core()
{
    delete params;
    delete solver;
    delete model;
}
