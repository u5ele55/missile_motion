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
    double h = params->missile.distanceBaseCM + 0.57 * params->missile.length - 0.16 * params->missile.diameter;
    
    double f_z = L*L / (params->missile.diameter * h) * (*Knm)(M);
    double q = (*atmosphere)(0).density * pow((*atmosphere)(0).soundSpeed, 2) * M*M * p / 2;
    double S_m = M_PI * pow(params->missile.diameter / 2, 2);
    
    // wind
    double w = params->environment.windVelocity;
    double a_w = params->environment.windAzimuth;
    double gamma_w = params->environment.windElevationAngle;
    
    double w_x = w * cos(a_w) * sin(gamma_w);
    double w_y = w * sin(gamma_w);
    double w_z = w * cos(a_w) * cos(gamma_w);

    double w_x_k = w_x * cos(theta) * cos(psi) + w_y * sin(theta) - w_z * cos(theta) * sin(psi);
    double w_y_k = -w_x * sin(theta) * cos(psi) + w_y * sin(theta) - w_z * cos(theta) * sin(psi);
    double w_z_k = w_x * sin(psi) + w_z * cos(psi);

    double V_x = v_k - w_x_k, V_y = -w_y_k, V_z = -w_z_k;
    double V = sqrt(V_x*V_x + V_y*V_y + V_z*V_z);

    double eps_w2 = asin(-w_y_k/V);
    double eps_w1 = asin(w_z_k/(V*cos(eps_w2)));
    // a.r. parts of de
    double qSmixCx = q * S_m * i_x * (*Cx)(M);
    double v_k_d_ar = -qSmixCx * cos(eps_w1) * sin(eps_w2) / m;
    double theta_d_ar = -qSmixCx * sin(eps_w2) / (m * v_k);
    double psi_d_ar = -qSmixCx * sin(eps_w1) * cos(eps_w2) / (m * v_k * cos(theta));
    // right side
    double drag = 0.5 * atm.density * S_m * (*Cx)(y) * v_k*v_k; // not from GOST
    double v_k_d = -g * sin(theta) + v_k_d_ar - drag / m;
    double theta_d = -g * cos(theta) / v_k + theta_d_ar;
    double psi_d = -i_z * f_z * J_x * omega_x * theta_d / (L * m * v_k * cos(theta)) + psi_d_ar;


    double x_d = v_k * cos(theta) * cos(psi);
    double y_d = v_k * sin(theta);
    double z_d = -v_k * cos(theta) * sin(psi);

    double omega_x_d = -m_omega_x * p * q * S_m * L*L * omega_x / (J_x * v_k);
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
