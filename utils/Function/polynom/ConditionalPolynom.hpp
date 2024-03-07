#pragma once

#include "Function/polynom/Polynom.hpp"

class ConditionalPolynom : Function<double, double>
{
private:
    std::vector< std::pair<double, Polynom*> > use;
public:
    ConditionalPolynom(
        std::vector<double> conditions,
        std::vector<int> degrees,
        std::vector<std::vector<double>> coefs
    );
    double operator()(double x);
    virtual ~ConditionalPolynom() {
        for (auto& u : use)
            delete u.second;
    }
};