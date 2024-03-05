#include "ParametersInputter.hpp"
#include <cmath>

ParametersInputter::ParametersInputter(
    const std::string &missileFilename, const std::string &launchFilename
)   : missileFile(missileFilename),
    launchFile(launchFilename)
{}

Parameters *ParametersInputter::create()
{
    auto toRad = [](double &deg) {
        deg *= M_PI / 180;
    };

    MissileParameters missile;
    missileFile 
        >> missile.type 
        >> missile.mass 
        >> missile.length
        >> missile.diameter
        >> missile.distanceBaseCM
        >> missile.lengthHead
        >> missile.axialInertiaMoment
        >> missile.formCoefficient
        >> missile.derivationCoefficient
        >> missile.axialDumpingMomentCoefficient;

    LaunchParameters launch;
    launchFile 
        >> launch.azimuth
        >> launch.velocity
        >> launch.elevationAngle
        >> launch.headingAngle
        >> launch.axialAngularVelocity;
    
    toRad(launch.azimuth);
    toRad(launch.elevationAngle);
    toRad(launch.headingAngle);

    LaunchLocation location;
    launchFile 
        >> location.distance
        >> location.height
        >> location.lateralDeviaton
        >> location.startHeightAboveEarth
        >> location.finalHeightAboveEarth;
    
    EnvironmentParameters environment;
    launchFile 
        >> environment.windVelocity
        >> environment.windAzimuth
        >> environment.windElevationAngle;

    toRad(environment.windAzimuth);
    toRad(environment.windElevationAngle);

    ModelingParameters modeling;
    launchFile 
        >> modeling.integrationStep
        >> modeling.measurementsInterval
        >> modeling.measurementsStep
        >> modeling.measurementsStart
        >> modeling.measurementsMSE
        >> modeling.approxPolynomDegree
        >> modeling.tests;


    Parameters *res = new Parameters;
    res->missile = missile;
    res->launch = launch;
    res->location = location;
    res->environment = environment;
    res->modeling = modeling;

    return res;
}

ParametersInputter::~ParametersInputter()
{
    launchFile.close();
    missileFile.close();
}