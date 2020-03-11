#include "task1.hpp"

Eigen::MatrixXd task1::simulate_sys(Eigen::VectorXd y0, double t0, int n){
    euler_eq_simu.seth(_h);
    Eigen::MatrixXd _outPut(y0.rows(), n+1);
    _outPut = euler_eq_simu.rk4(y0, t0, n);
    return _outPut;
}

Eigen::MatrixXd task1::simulate_env(Eigen::VectorXd y0, double t0, int n){
    euler_eq_true.seth(_h);
    return euler_eq_true.rk4(y0, t0, n);
}

int task1::set_w_func(std::function<Eigen::Vector3d (double, Eigen::VectorXd)>& w_func){
    //w_func should be defined to generate w from t and y
    //ydot WITH external force
    std::function<Eigen::VectorXd(double, Eigen::VectorXd)> ydot_with_w = [&](double t, Eigen::VectorXd yin){
        return ydot(t, yin, w_func(t, yin));
    };
    euler_eq_true.set_func(ydot_with_w);
    return 0;
}
