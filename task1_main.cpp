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

    std::cout << "3";

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

    return 0;
}
