#include <iostream>
#include "PID.h"

using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp_init, double Ki_init, double Kd_init) {
    Kp = Kp_init;
    Ki = Ki_init;
    Kd = Kd_init;
    cte_previous = 0.;
    total_error = 0.;
}

void PID::UpdateError(double cte) {
    p_error = cte;
    d_error = cte - cte_previous; // divided by time
    i_error = total_error + cte;
    cte_previous = cte;
}

double PID::TotalError() {
    total_error = -Kp * p_error - Kd * d_error - Ki * i_error;
    return total_error;
}

