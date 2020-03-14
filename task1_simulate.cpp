#include "task1.hpp"
#include <boost/math/special_functions.hpp>
#include <cmath>

Eigen::MatrixXd task1::simulate_sys(Eigen::VectorXd y0, double t0, int n){
    euler_eq_simu.seth(_h);
    Eigen::MatrixXd _outPut(y0.rows(), n+1);
    _outPut = euler_eq_simu.rk4_steps(y0, t0, n);
    return _outPut;
}

Eigen::MatrixXd task1::simulate_env(Eigen::VectorXd y0, double t0, int n){
    euler_eq_true.seth(_h);
    Eigen::MatrixXd _outPut(y0.rows(), n+1);
    _outPut=euler_eq_true.rk4_steps(y0, t0, n);
    return _outPut;
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

Eigen::MatrixXd task1::analytic_omega(Eigen::VectorXd r0, double t0, int n){
    Eigen::MatrixXd _out(3,n+1);
    Eigen::Matrix3d In=Eigen::MatrixXd::Identity(3,3);
    In(0,0)=_Ixx;
    In(1,1)=_Iyy;
    In(2,2)=_Izz;
    Eigen::Vector3d L=In*r0.segment(4,3);

    _L2=L.squaredNorm();
    _2T=L.dot(r0.segment(4,3));

    _alphax=std::sqrt((_L2-_2T*_Iyy)/(_Ixx*(_Ixx-_Iyy)));
    _alphay=std::sqrt((_2T*_Izz-_L2)/(_Iyy*(_Izz-_Iyy)));
    _alphaz=std::sqrt((_L2-_2T*_Iyy)/(_Izz*(_Izz-_Iyy)));
    _beta=(_Iyy-_Izz)/_Ixx * _alphay*_alphaz/_alphax;
    _k=std::sqrt((_Izz-_Ixx)*(_L2-_2T*_Iyy)/(_Ixx-_Iyy)/(_2T*_Izz-_L2));

    std::cout<<_alphax<<std::endl
        <<_alphay<<std::endl
        <<_alphaz<<std::endl
        <<_beta<<std::endl
        <<_k<<std::endl;

    _delta=boost::math::ellint_1(_k, 0.5*std::acos(-1));

    for(int i=0; i<=n; i++){
        _out(0,i)=_omegax_analytic(0.1*i);
        _out(1,i)=_omegay_analytic(0.1*i);
        _out(2,i)=_omegaz_analytic(0.1*i);
    }

    return _out;
}

double task1::_omegax_analytic(double t){
    return _alphax*boost::math::jacobi_sn(_k, _beta*t + _delta);
}
double task1::_omegay_analytic(double t){
    return _alphay*boost::math::jacobi_dn(_k, _beta*t + _delta);
}
double task1::_omegaz_analytic(double t){
    return _alphaz*boost::math::jacobi_cn(_k, _beta*t + _delta);
}
