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
    double pi_0 = pow(1 - Constants::Common::G * (Constants::Earth::MAJOR_AXIS + 1), 5.4); // approximation

    Vector startBLH = {0, 0, 2};
    auto startECEF = blh2ecef(startBLH);
    std::cout << params->launch.elevationAngle << " " << params->launch.headingAngle << '\n';
    model = new MissileSystem(params, {
        params->launch.velocity,
        params->launch.elevationAngle,
        params->launch.headingAngle,
        0,
        0,
        0,
        params->launch.axialAngularVelocity,
        pi_0
    });
    solver = new RK4Solver(
        model,
        0.05 
        //params->modeling.integrationStep
    );

    std::ofstream file("trajectory.txt");

    for(int i = 0; i < 150; i ++) {
        const auto &state = solver->solve(i);
        // std::cout << i << " " << state << '\n';
        Vector r = {state[3], state[4], state[5]};
        file << r << '\n';
    }
}

Core::~Core()
{
    delete params;
    delete solver;
    delete model;
}
