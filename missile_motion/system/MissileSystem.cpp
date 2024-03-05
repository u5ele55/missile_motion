#include "MissileSystem.hpp"
#include "global/GlobalScope.hpp"
#include "global/Constants.hpp"
#include "LinAlg.hpp"

#include <cmath>

MissileSystem::MissileSystem(Parameters *params, Vector initialState)
    : params(params),
    initialState(initialState)
{
    auto &scope = GlobalScope::getInstance();

    atmosphere = &scope.getAtmosphereParamsEvaluator();
    
}

void MissileSystem::f(Vector &state, double time) const
{
    double v_k = state[0], theta = state[1], psi = state[2];
    double x = state[3], y = state[4], z = state[5];
    double omega_x = state[6], p = state[7];

    // TODO: write DE's
}

Vector MissileSystem::getInitialState() const
{
    return initialState;
}
