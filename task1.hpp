#ifndef H1_H
#define H1_H

#include <Eigen/Dense>
#include <my/RK.hpp>

class task1{
    Eigen::Vector3d w_none;

    double _Ixx;
    double _Iyy;
    double _Izz;
    std::function<Eigen::VectorXd(double, Eigen::VectorXd, Eigen::Vector3d)> ydot;

    double _h;
    bool _w_is_not_set;
    my::RK euler_eq_simu;
    my::RK euler_eq_true;

    Eigen::MatrixXd _simulate(Eigen::VectorXd r0, double t0, int n, my::RK& propagator);

    public:
    int h(double hin);

    //simulator WITHOUT external force
    Eigen::MatrixXd simulate_sys(Eigen::VectorXd r0, double t0, int n);

    //define external force
    int set_w_func(std::function<Eigen::Vector3d(double, Eigen::VectorXd)>& w_func);
    //simulator WITH external force
    Eigen::MatrixXd simulate_env(Eigen::VectorXd r0, double t0, int n);
    task1();
};
#endif
