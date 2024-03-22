#pragma once

struct MissileParameters {
    std::string type;
    double mass;
    double length;
    double diameter;
    double distanceBaseCM;
    double lengthHead;
    double axialInertiaMoment;
    double formCoefficient;
    double derivationCoefficient;
    double axialDumpingMomentCoefficient;
};

struct LaunchParameters {
    double azimuth;
    double velocity;
    double axialAngularVelocity;
    double elevationAngle;
    double headingAngle;
};

struct LaunchLocation {
    double distance; // X
    double height; // Y
    double lateralDeviaton; // Z
    double startHeightAboveEarth;
    double finalHeightAboveEarth;
};

struct EnvironmentParameters {
    double windVelocity;
    double windAzimuth;
    double windElevationAngle;
};

struct ModelingParameters {
    double integrationStep;
    double measurementsInterval;
    double measurementsStep;
    double measurementsStart;
    double measurementsMSE;
    int approxPolynomDegree;
    int tests;
};

struct Parameters
{
    MissileParameters missile;
    LaunchParameters launch;
    LaunchLocation location;
    EnvironmentParameters environment;
    ModelingParameters modeling;
};