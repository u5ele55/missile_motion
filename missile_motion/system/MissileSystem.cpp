#include "MissileSystem.hpp"
#include "global/GlobalScope.hpp"
#include "global/Constants.hpp"
#include "LinAlg.hpp"

#include <cmath>

MissileSystem::MissileSystem(Parameters *params, Vector initialCoordinates, Vector initialVelocity)
    : params(params),
    initialState({
        initialCoordinates[0], 
        initialCoordinates[1], 
        initialCoordinates[2], 
        initialVelocity[0], 
        initialVelocity[1], 
        initialVelocity[2]
    }),
    initialCoordinates(initialCoordinates)
{
    auto &scope = GlobalScope::getInstance();

    atmosphere = &scope.getAtmosphereParamsEvaluator();
    
}

void MissileSystem::f(Vector &state, double time) const
{
    double x = state[0], y = state[1], z = state[2];
    double vx = state[3], vy = state[4], vz = state[5];

    // TODO: write DE's
}

Vector MissileSystem::getInitialState() const
{
    return initialState;
}
