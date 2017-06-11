#ifndef PID_H
#define PID_H

class PID {
public:
    /*
    * Errors
    */
    double total_error;
    double cte_previous;

    double p_error;
    double p_error_prev;

    double i_error;
    double i_error_prev;

    double d_error;
    double d_error_prev;

    /*
    * Coefficients
    */
    double Kp;
    double Ki;
    double Kd;

    /*
    * Constructor
    */
    PID();

    /*
    * Destructor.
    */
    virtual ~PID();

    /*
    * Initialize PID.
    */
    void Init(double Kp, double Ki, double Kd);

    /*
    * Update the PID error variables given cross track error.
    */
    void UpdateError(double cte);

    /*
    * Calculate the total PID error.
    */
    double TotalError();
};

#endif /* PID_H */
