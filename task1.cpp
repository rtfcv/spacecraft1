#include"task1.hpp"
#include<iostream>
#include <functional>

task1::task1(){
    //define function to integrate
    std::function<Eigen::VectorXd(double, Eigen::VectorXd, Eigen::Vector3d)> ydot = [&](double t, Eigen::VectorXd yin, Eigen::Vector3d win){
        Eigen::Vector4d q = yin.segment(0,3);
        double omegax=yin(4);
        double omegay=yin(5);
        double omegaz=yin(6);
        Eigen::VectorXd _ydot(7);

        _ydot(0) = 0.5*(-omegax*q(1)-omegay*q(2)-omegaz*q(3));
        _ydot(1) = 0.5*(+omegax*q(0)-omegay*q(3)+omegaz*q(2));
        _ydot(2) = 0.5*(+omegax*q(3)+omegay*q(0)-omegaz*q(1));
        _ydot(3) = 0.5*(-omegax*q(2)+omegay*q(1)+omegaz*q(0));

        _ydot(4) = (+_Iyy*omegay*omegaz-_Izz*omegay*omegaz+win(0))/_Ixx;

        return _ydot;
    };

    //ydot with no external force
    std::function<Eigen::VectorXd(double, Eigen::VectorXd)> ydot_no_w = [&](double t, Eigen::VectorXd yin){
        return ydot(t, yin, w_none);
    };

    //ydot with no external force
    std::function<Eigen::VectorXd(double, Eigen::VectorXd)> ydot_with_w = [&](double t, Eigen::VectorXd yin){
        Eigen::Vector3d w_rand;
        //generate random w here
        return ydot(t, yin, w_rand);
    };

    euler_eq_simu.set_func(ydot_no_w);
    euler_eq_true.set_func(ydot_no_w);
}

