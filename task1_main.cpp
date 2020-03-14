#include <iostream>
#include <cmath>
#include <Eigen/Dense>
#include "task1.hpp"
#include "save.hpp"

int main(){
    double _pi = std::acos(-1);
    double h=0.1;
    task1 _task1;
    _task1.h(h);
    int n = 1000;
    Eigen::VectorXd y0(7);


    double omegas = 17.0/60.0 *2*_pi;
    y0 << 1.0 , 0.0, 0.0, 0.0, 0.1, omegas + 0.1, 0.0;


    Eigen::MatrixXd res1(7,n+1);
    res1 = _task1.simulate_sys(y0, 0, n);

    Eigen::MatrixXd res2(3,n+1);
    res2 = _task1.analytic_omega(y0, 0, n);

    Eigen::VectorXd time(n+1);
    for(int i=0; i <= n; i++){
        time(i)=h*i;
    }

    //now save result
    savexy(time, res1.row(0), "q0_k1.dat");
    savexy(time, res1.row(1), "q1_k1.dat");
    savexy(time, res1.row(2), "q2_k1.dat");
    savexy(time, res1.row(3), "q3_k1.dat");

    savexy(time, res1.row(4), "omega0_k1.dat");
    savexy(time, res1.row(5), "omega1_k1.dat");
    savexy(time, res1.row(6), "omega2_k1.dat");

    savexy(time, res2.row(0), "omega0_k1_analytic.dat");
    savexy(time, res2.row(1), "omega1_k1_analytic.dat");
    savexy(time, res2.row(2), "omega2_k1_analytic.dat");

    Eigen::MatrixXd res3=res2;
    
    

    res3.row(0)=res1.row(4)-res3.row(0);
    res3.row(1)=res1.row(5)-res3.row(1);    
    res3.row(2)=res1.row(6)-res3.row(2);

    savexy(time, res3.row(0), "omega0_k1_delta.dat");
    savexy(time, res3.row(1), "omega1_k1_delta.dat");
    savexy(time, res3.row(2), "omega2_k1_delta.dat");

    return 0;
}
