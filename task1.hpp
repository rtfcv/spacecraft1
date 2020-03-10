#ifndef H2_H
#define H2_H

#include <Eigen/Dense>
#include <my/RK.h>

class task1{
    Eigen::Vector3d w_none;

    double _Ixx;
    double _Iyy;
    double _Izz;

    double _h;
    my::RK euler_eq_simu;
    my::RK euler_eq_true;

    public:
    float h();
    Eigen::MatrixXd calcY(Eigen::VectorXd y0, float t0, int n);
    task1();
};

#endif
