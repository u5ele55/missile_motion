#pragma once
#include "IFileInputter.hpp"
#include "missile_motion/system/Parameters.hpp"

class ParametersInputter : IFileInputter<Parameters>
{
private:
    std::ifstream missileFile;
    std::ifstream launchFile;
public:
    ParametersInputter(
        const std::string& missileFilename,
        const std::string& launchFilename
    );
    Parameters* create();
    ~ParametersInputter();
};