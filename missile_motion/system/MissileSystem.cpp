#include "MissileSystem.hpp"
#include "global/GlobalScope.hpp"
#include "global/Constants.hpp"
#include "LinAlg.hpp"
#include "Function/physics/VirtualTemperature.hpp"

#include <cmath>

MissileSystem::MissileSystem(Parameters *params, Vector initialState)
    : params(params),
    initialState(initialState)
{
    auto &scope = GlobalScope::getInstance();

    atmosphere = scope.getAtmosphereParamsEvaluator();
    virtualTemperature = new VirtualTemperature;
    axialDumpingMoment = scope.getAxialDumpingMomentEvaluator();
    Cx = scope.getCxEvaluator();
    Knm = scope.getKnmEvaluator();
}

MissileSystem::~MissileSystem()
{
    delete virtualTemperature;
}
#include <iostream>
void MissileSystem::f(Vector &state, double time) const
{
    double v_k = state[0], theta = state[1], psi = state[2];
    double x = state[3], y = state[4], z = state[5];
    double omega_x = state[6], p = state[7];

    // if fell
    if (y < 0) {
        state = Vector(8); // {0, 0, 0, 0, 0, 0, 0, 0};
        return;
    }

    auto atm = (*atmosphere)(y);
    
    double g = 9.81;
    double i_z = params->missile.derivationCoefficient;
    double i_x = params->missile.formCoefficient;
    double J_x = params->missile.axialInertiaMoment;
    double L = params->missile.length, m = params->missile.mass;
    double M = v_k / atm.soundSpeed; 
    double tau = (*virtualTemperature)(y);
    double m_omega_x = (*axialDumpingMoment)(M);
    double h = params->missile.distanceBaseCM + 0.57 * params->missile.lengthHead - 0.16 * params->missile.diameter;
    
    double f_z = L*L / (params->missile.diameter * h) * (*Knm)(M);
    double q = (*atmosphere)(0).density * pow((*atmosphere)(0).soundSpeed, 2) * M*M * p / 2;
    double S_m = M_PI * pow(params->missile.diameter / 2, 2);
    
    // wind
    double w = params->environment.windVelocity;
    double a_w = params->environment.windAzimuth;
    double gamma_w = params->environment.windElevationAngle;

    double angle = a_w - (params->launch.azimuth - psi); // todo

    double w_x_k = -w * cos(angle) * cos(theta);
    double w_y_k = w * cos(angle) * sin(theta);
    double w_z_k = -w * sin(angle);

    double V_x = v_k - w_x_k, V_y = -w_y_k, V_z = -w_z_k;
    double V = sqrt(V_x*V_x + V_y*V_y + V_z*V_z);

    double eps_w2 = asin(-w_y_k/V);
    double eps_w1 = asin(w_z_k/(V*cos(eps_w2)));

    // C_k
    double C_x_k_M = (*Cx)(M) * i_x; // simplified
    double delta_C_x_k_eps_w = C_x_k_M * (cos(eps_w1) * cos(eps_w2) - 1);    
    double C_x_k = C_x_k_M + delta_C_x_k_eps_w; 

    double C_y_k = C_x_k_M * sin(eps_w2);

    double C_z_k = C_x_k_M * sin(eps_w1) * cos(eps_w2);

    // right side
    double v_k_d = -g * sin(theta) - q * S_m * C_x_k / m;
    double theta_d = -g * cos(theta) / v_k - C_y_k * q * S_m / (m*v_k);
    double psi_d = -i_z * f_z * J_x * omega_x * theta_d / (L*m*v_k*cos(theta)) - C_z_k * q * S_m / (m*v_k*cos(theta));

    double x_d = v_k * cos(theta) * cos(psi);
    double y_d = v_k * sin(theta);
    double z_d = -v_k * cos(theta) * sin(psi);

    double omega_x_d = -m_omega_x * q * S_m * L*L * omega_x / (J_x * v_k);
    double p_d = -g * p * y_d / (Constants::Common::R * tau);

    state[0] = v_k_d;
    state[1] = theta_d;
    state[2] = psi_d;
    
    state[3] = x_d;
    state[4] = y_d;
    state[5] = z_d;

    state[6] = omega_x_d;
    state[7] = p_d;
}

Vector MissileSystem::getInitialState() const
{
    return initialState;
}
