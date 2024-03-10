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
    solver(nullptr),
    flightTime(-1)
{
    ParametersInputter paramsCreator(
        FILENAMES.at("missile"), FILENAMES.at("launch")
    );
    params = paramsCreator.create();

    GlobalScope::getInstance().setParameters(params);
}

Vector Core::calculateEndpoint()
{
    double G_tau_1 = -6.328e-3; 
    double pi_0 = pow(1 - G_tau_1 * params->location.height, 5.4); // approximation
    
    model = new MissileSystem(params, {
        params->launch.velocity,
        params->launch.elevationAngle,
        params->launch.headingAngle,
        params->location.distance,
        params->location.height,
        params->location.lateralDeviaton,
        params->launch.axialAngularVelocity,
        pi_0
    });
    solver = new RK4Solver(
        model,
        params->modeling.integrationStep
    );

    std::ofstream file("trajectory.txt");

    Vector state(8);
    Vector lastState(8);

    for(int i = 0; i < 150; i ++) {
        lastState = state;
        state = solver->solve(i);
        Vector r = {state[3], state[4], state[5]};
        std::cout << i << " " << state << '\n';
        file << r << '\n';
        if (lastState == state) {
            flightTime = i;
            break;
        }
    }
    std::cout << "Flight time: " << flightTime << " s \n";
    return {state[3], state[4], state[5]};
}

Core::~Core()
{
    delete params;
    delete solver;
    delete model;
}
