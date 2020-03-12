#include "task2.hpp"
#include "save.hpp"
#include <iostream>
#include <Eigen/Dense>

int main(){
    double _pi = std::acos(-1);
    double h=0.1;
    double omegas = 17.0/60.0 *2*_pi;
    Eigen::VectorXd y0env(7);
    y0env << 1.0, 0.0, 0.0, 0.0, 0.1, omegas + 0.1, 0.0;

    task2 _task2(123, 62, 331);
    _task2.simulate_sym_filtered(100, y0env);
    _task2.save();
    return 0;
}
