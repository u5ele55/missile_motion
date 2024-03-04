#pragma once

#include "Vector.hpp"
#include "file_input/ParametersInputter.hpp"
#include "missile_motion/modeling/AbstractSolver.hpp"

class Core
{
private:
    Parameters * params;
    AbstractSolver * solver;
    ISystem * model;
public:
    Core();

    Vector calculateEndpoint();

    ~Core();
};
