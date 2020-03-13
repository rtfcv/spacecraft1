#ifndef H2_H
#define H2_H
#include "task1.hpp"
#include <random>
#include <functional>
#include <Eigen/Dense>

class task2{
    int _steps_between_observations;
    bool _env_simulation_done;
    std::mt19937 _mt; //just for test
    std::uniform_int_distribution<> _rnd_int123;

//random number generator for w
    std::mt19937 _mtw0;
    std::mt19937 _mtw1;
    std::mt19937 _mtw2;

//random number generator for obserbation
    std::mt19937 _mto0;
    std::mt19937 _mto1;
    std::mt19937 _mto2;

//generic random number stuffs
    std::random_device _rnd;
    std::normal_distribution<> _norm; 
    int _seed;
    int _seed_col;
    int _seed_obs;

//actual generator for w vector
    std::function<Eigen::Vector3d (double, Eigen::VectorXd)> w_func;

    double _Ixx;
    double _Iyy;
    double _Izz;

    task1 _task1;
    double _h_obs;
    double _h_sim;

    //functions for use in simulator
    Eigen::MatrixXd _A(Eigen::VectorXd);
    Eigen::MatrixXd _H1(Eigen::VectorXd);
    Eigen::MatrixXd _H2(Eigen::VectorXd);
    Eigen::MatrixXd _H3(Eigen::VectorXd);

    Eigen::Vector3d _Zeta1(Eigen::VectorXd);
    Eigen::Vector3d _Zeta2(Eigen::VectorXd);
    Eigen::Vector3d _Zeta3(Eigen::VectorXd);

    Eigen::MatrixXd _B;
    Eigen::Matrix3d _Qprime;
    Eigen::Matrix3d _R;

    //result variables
    Eigen::MatrixXd _y_env_result;
    Eigen::MatrixXd _y_sim_result;
    Eigen::MatrixXd _P_diag_result;
    Eigen::VectorXd _i_eq_1;
    Eigen::VectorXd _i_eq_2;
    Eigen::VectorXd _i_eq_3;

public:
    task2();
    task2(int, int, int);

    int set_seed(int, int, int);
    int set_h_obs(double);
    int set_I(double, double, double);
    int set_stdev_w(double);
    int set_stdev_v(double);
    int simulate_sym_filtered(int, Eigen::VectorXd, Eigen::VectorXd);
    int save();
    void __test(int);
};

#endif
