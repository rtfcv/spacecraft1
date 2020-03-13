#include "task2.hpp"
#include "save.hpp"
#include <iostream>
#include <Eigen/Dense>
#include <my/ini.h>

int main(){
    double _pi = std::acos(-1);
    double h=0.1;
    double omegas = 17.0/60.0 *2*_pi;

    my::ini _config("param.ini");
    double omegax=_config.dread("init.omegax");
    double omegay=_config.dread("init.omegay");
    double omegaz=_config.dread("init.omegaz");

    double q0=_config.dread("init.q0");
    double q1=_config.dread("init.q1");
    double q2=_config.dread("init.q2");
    double q3=_config.dread("init.q3");

    int _steps=_config.read<int>("init.steps");

    int seed_w=_config.read<int>("seed.w");
    int seed_col=_config.read<int>("seed.col");
    int seed_v=_config.read<int>("seed.v");

    //this should remain constant
    Eigen::VectorXd y0env(7);
    y0env << 1.0, 0.0, 0.0, 0.0, 0.1, omegas + 0.1, 0.0;

    Eigen::Vector4d _q_init(q0,q1,q2,q3);
    _q_init=_q_init/_q_init.norm();
    Eigen::VectorXd y0sim(7);
    y0sim << _q_init(0), _q_init(1), _q_init(2), _q_init(3), omegax, omegay, omegaz;

    task2 _task2(123, 62, 331);
    _task2.simulate_sym_filtered(_steps, y0env, y0sim);
    _task2.save();

    std::cout<<"simulation finished after "<<_steps<<" steps\n"<<std::endl;
    std::cout<<"y0 was"<<std::endl;
    std::cout<<y0sim<<std::endl;
    std::cout<<"\ninitial seed was"<<std::endl;
    std::cout<<"seed_w = "<<seed_w<<std::endl;
    std::cout<<"seed_col = "<<seed_col<<std::endl;
    std::cout<<"seed_v = "<<seed_v<<std::endl;
    return 0;
}
