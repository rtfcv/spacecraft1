#include"task2.hpp"
#include"save.hpp"
#include<iostream>

task2::task2(){
    _steps_between_observations=10;
    set_I(1.9, 1.6, 2.0);
    set_h_obs(1);
    set_stdev_v(0.01);
    set_stdev_w(0.01);

    //set the seed
    set_seed(123, 62, 331);
}

task2::task2(int seed_w, int seed_col, int seed_obs){
    _steps_between_observations=10;
    set_I(1.9, 1.6, 2.0);
    set_h_obs(1);
    set_stdev_v(0.01);
    set_stdev_w(0.01);

    //set the seed
    set_seed(seed_w, seed_col, seed_obs);
}

int task2::set_stdev_v(double stdev){
    _R=Eigen::Matrix3d::Identity()*stdev*stdev;
    return 0;
}

int task2::set_stdev_w(double stdev){
    _Qprime=Eigen::Matrix3d::Identity()*0.5*stdev*stdev;
    return 0;
}

int task2::set_h_obs(double h_obs){
    _h_obs=h_obs;
    _h_sim=_h_obs/_steps_between_observations;
    _task1.h(_h_sim);
    return 0;
}

int task2::set_I(double Ixx, double Iyy, double Izz){
    _Ixx = Ixx;
    _Iyy = Iyy;
    _Izz = Izz;

    _B.resize(7,3);
    _B << 0, 0, 0,
          0, 0, 0,
          0, 0, 0,
          0, 0, 0,
          1/_Ixx, 0, 0,
          0, 1/_Iyy, 0,
          0, 0, 1/_Izz;
    return 0;
}

int task2::set_seed(int seed_w, int seed_col, int seed_obs){
    //set the seed
    _seed=seed_w;
    _seed_obs=seed_obs;
    _seed_col=seed_col;

    //configure disributions based on above seed
    std::uniform_int_distribution<>::param_type param1(1,3);
    _rnd_int123.param(param1);
    _mt.seed(_seed_col);
    _mto0.seed(_seed_obs);
    _mto1.seed(_seed_obs-1);
    _mto2.seed(_seed_obs-2);
    std::normal_distribution<>::param_type my_param(0.0, 0.01);
    _norm.param(my_param);
    _mtw0.seed(_seed+0);
    _mtw1.seed(_seed+1);
    _mtw2.seed(_seed+2);

    //define function to randomly provide \bm{w}
    w_func = [&](double t, Eigen::VectorXd yin){
        _mtw0.seed(_mtw0());
        _mtw1.seed(_mtw1());
        _mtw2.seed(_mtw2());
        Eigen::Vector3d _w(_norm(_mtw0), _norm(_mtw1), _norm(_mtw2));
        std::cout<<"w on t="<<t<<std::endl;
        std::cout<<_w<<std::endl;
        return _w;
    };
    _task1.set_w_func(w_func);
    return 0;
}

int task2::save(){
    //Eigen::MatrixXd _y_env_result;
    //Eigen::MatrixXd _y_sim_result;
    //Eigen::MatrixXd _P_diag_result;
    int _n_y=_y_env_result.cols();
    int _n_obs=_P_diag_result.cols();
    Eigen::VectorXd _time_y(_n_y);
    Eigen::VectorXd _time_obs(_n_obs);

    for(int i=0; i<_n_y; i++){
        _time_y(i)=_h_sim*i;
    }
    for(int i=0; i<_n_obs; i++){
        _time_obs(i)=_h_obs*i;
    }

    savexy(_time_y, _y_env_result.row(0), "task2_q0_env.dat");
    savexy(_time_y, _y_env_result.row(1), "task2_q1_env.dat");
    savexy(_time_y, _y_env_result.row(2), "task2_q2_env.dat");
    savexy(_time_y, _y_env_result.row(3), "task2_q3_env.dat");
    savexy(_time_y, _y_env_result.row(4), "task2_omegax_env.dat");
    savexy(_time_y, _y_env_result.row(5), "task2_omegay_env.dat");
    savexy(_time_y, _y_env_result.row(6), "task2_omegaz_env.dat");

    savexy(_time_y, _y_sim_result.row(0), "task2_q0_sim.dat");
    savexy(_time_y, _y_sim_result.row(1), "task2_q1_sim.dat");
    savexy(_time_y, _y_sim_result.row(2), "task2_q2_sim.dat");
    savexy(_time_y, _y_sim_result.row(3), "task2_q3_sim.dat");
    savexy(_time_y, _y_sim_result.row(4), "task2_omegax_sim.dat");
    savexy(_time_y, _y_sim_result.row(5), "task2_omegay_sim.dat");
    savexy(_time_y, _y_sim_result.row(6), "task2_omegaz_sim.dat");

    savexy(_time_y, _y_env_result.row(0)-_y_sim_result.row(0), "task2_q0_delta.dat");
    savexy(_time_y, _y_env_result.row(1)-_y_sim_result.row(1), "task2_q1_delta.dat");
    savexy(_time_y, _y_env_result.row(2)-_y_sim_result.row(2), "task2_q2_delta.dat");
    savexy(_time_y, _y_env_result.row(3)-_y_sim_result.row(3), "task2_q3_delta.dat");
    savexy(_time_y, _y_env_result.row(4)-_y_sim_result.row(4), "task2_omegax_delta.dat");
    savexy(_time_y, _y_env_result.row(5)-_y_sim_result.row(5), "task2_omegay_delta.dat");
    savexy(_time_y, _y_env_result.row(6)-_y_sim_result.row(6), "task2_omegaz_delta.dat");

    savexy(_time_obs, _P_diag_result.row(0), "task2_P11.dat");
    savexy(_time_obs, _P_diag_result.row(1), "task2_P22.dat");
    savexy(_time_obs, _P_diag_result.row(2), "task2_P33.dat");
    savexy(_time_obs, _P_diag_result.row(3), "task2_P44.dat");
    savexy(_time_obs, _P_diag_result.row(4), "task2_P55.dat");
    savexy(_time_obs, _P_diag_result.row(5), "task2_P66.dat");
    savexy(_time_obs, _P_diag_result.row(6), "task2_P77.dat");

    savexy(_time_obs, _i_eq_1, "col_1.dat");
    savexy(_time_obs, _i_eq_2, "col_2.dat");
    savexy(_time_obs, _i_eq_3, "col_3.dat");
    return 0;
}

void task2::__test(int seed){
    //apply the parameter to the normal disribution _norm
    std::normal_distribution<>::param_type my_param(0.0, 0.01);
    _norm.param(my_param);

    std::cout<<"norm using seed 0:10"<<std::endl;
    for(int i; i<10; i++){
        _mt.seed(i);
        std::cout << _norm(_mt) << std::endl;
    }

    std::cout<<"norm using seed 1"<<std::endl;
    for(int i; i<10; i++){
        _mt.seed(1);
        std::cout << _norm(_mt) << std::endl;
    }

    std::cout<<"mt using seed 0:10"<<std::endl;
    for(int i; i<10; i++){
        _mt.seed(i);
        std::cout << _mt() << std::endl;
    }

    std::cout<<"mt using seed 1"<<std::endl;
    for(int i; i<10; i++){
        _mt.seed(1);
        std::cout << _mt() << std::endl;
    }

    _mt.seed(1);
    std::cout<<"mt using seed 1"<<std::endl;
    for(int i; i<10; i++){
        _mt.seed(_mt());
        std::cout << _mt() << std::endl;
    }
}
