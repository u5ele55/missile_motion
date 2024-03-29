#pragma once
#include <map>
#include <string>

const std::map<std::string, std::string> FILENAMES = {
    {"missile", "../datafiles/parameters/missile.txt"},
    {"launch", "../datafiles/parameters/launch.txt"},

    {"axial_dumping_moment", "../datafiles/interpolation/axial_dumping_moment.txt"},

    {"C_x", "../datafiles/polynoms/C_x.txt"},
    {"K_nm", "../datafiles/polynoms/K_nm.txt"},
};