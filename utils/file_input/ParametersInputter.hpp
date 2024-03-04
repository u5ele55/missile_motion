#pragma once
#include "IFileInputter.hpp"
#include "missile_motion/system/Parameters.hpp"

class ParametersInputter : IFileInputter<Parameters>
{
private:
    std::ifstream file;
public:
    ParametersInputter(const std::string& filename);
    Parameters* create();
    ~ParametersInputter();
};