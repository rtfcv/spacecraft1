#import "task2.hpp"
#import <cmath>

int task2::simulate_sym_filtered(int t, Eigen::VectorXd y0){
    _y_env_result.resize(7, t*_steps_between_observations + 1);
    _y_sim_result.resize(7, t*_steps_between_observations + 1);
    _P_diag_result.resize(7, t);
    
    //save the result for the actual value
    _y_env_result=_task1.simulate_env(y0, 0, t*_steps_between_observations);

    Eigen::MatrixXd _sim_res(7, 1+_steps_between_observations);
    int i=0;

    Eigen::MatrixXd Phi_n(7,7);
    Eigen::MatrixXd I=Eigen::MatrixXd::Identity(7,7);
    Eigen::MatrixXd IAinv(7,7);
    Eigen::MatrixXd Gamma_n(7,3);
    Eigen::MatrixXd P_n=I;
    Eigen::MatrixXd P_nt1(7,7);
    Eigen::MatrixXd M_nt1(7,7);
    Eigen::MatrixXd H_int1(7,3);
    Eigen::MatrixXd K_nt1(7,7);

    Eigen::VectorXd yn=y0;
    Eigen::VectorXd ynt1=y0;
    Eigen::VectorXd xhat=0*y0;
    Eigen::VectorXd xbar=0*y0;
    Eigen::VectorXd z_int1=0*y0;
    Eigen::Vector3d v(0,0,0);

    _P_diag_result.col(0) << std::sqrt(P_n(0,0)), std::sqrt(P_n(1,1)),
        std::sqrt(P_n(2,2)), std::sqrt(P_n(3,3)), std::sqrt(P_n(4,4)),
        std::sqrt(P_n(7,7)), std::sqrt(P_n(6,6));

    for (int n=0; n<t; n++){  //n corresponds to number of observations
        yn=ynt1+xhat;  //assert previous result into y_n

        //calculate from nth observation up to (n+1)th observation
        _sim_res=_task1.simulate_sys(yn, n, _steps_between_observations);
        Eigen::VectorXd ynt1=_sim_res.row(_steps_between_observations-1);

        IAinv=I-_A(ynt1);
        IAinv=IAinv.inverse();
        Phi_n=IAinv*(I+0.5*_A(yn));
        Gamma_n=IAinv*_B*_h_obs;
        M_nt1=Phi_n*P_n*Phi_n.transpose() + Gamma_n*_Qprime*Gamma_n.transpose();

        //observation kicks in
        i=_rnd_int123(_mt);
        v << _norm(_mto0), _norm(_mto1), _norm(_mto2);
        _mto0.seed(_mto0());
        _mto1.seed(_mto1());
        _mto2.seed(_mto2());
        _mt.seed(_mt());
        switch (i) {
            case 1:
                H_int1=_H1(ynt1);
                z_int1=_Zeta1(_y_env_result.col(n*_steps_between_observations))
                    -_Zeta1(ynt1)+v;
                break;
            case 2:
                H_int1=_H2(ynt1);
                z_int1=_Zeta2(_y_env_result.col(n*_steps_between_observations))
                    -_Zeta2(ynt1)+v;
                break;
            case 3:
                H_int1=_H3(ynt1);
                z_int1=_Zeta3(_y_env_result.col(n*_steps_between_observations))
                    -_Zeta3(ynt1)+v;
                break;
        }

        P_nt1=M_nt1.inverse() + H_int1.transpose()*_R*H_int1;
        P_nt1=P_nt1.inverse();
        K_nt1=P_nt1*H_int1.transpose()*_R.inverse();
        xhat=K_nt1*z_int1;

        //save the results
        _y_sim_result.block(0,1+n*_steps_between_observations,
                7, _steps_between_observations)=_sim_res; //internal values
        _P_diag_result.col(n) << std::sqrt(P_nt1(0,0)), std::sqrt(P_nt1(1,1)),
            std::sqrt(P_nt1(2,2)), std::sqrt(P_nt1(3,3)), std::sqrt(P_nt1(4,4)),
            std::sqrt(P_nt1(7,7)), std::sqrt(P_nt1(6,6)); //standard deviation
    }
    return 0;
}

Eigen::MatrixXd task2::_A(Eigen::VectorXd yin){
    Eigen::Vector4d q = yin.segment(0,4);
    double omegax=yin(4);
    double omegay=yin(5);
    double omegaz=yin(6);
    Eigen::MatrixXd _output=Eigen::MatrixXd::Zero(7,7);

    _output.block(0,0,4,4) <<          0, -0.5*omegax, -0.5*omegay, -0.5*omegaz,
                              0.5*omegax,           0,  0.5*omegaz, -0.5*omegay,
                              0.5*omegay, -0.5*omegaz,           0,  0.5*omegax,
                              0.5*omegaz,  0.5*omegay, -0.5*omegax,           0;
    _output.block(0,4,4,3) << -0.5*q(1), -0.5*q(2), -0.5*q(3),
                               0.5*q(0), -0.5*q(3),  0.5*q(2),
                               0.5*q(3),  0.5*q(0), -0.5*q(1),
                              -0.5*q(2),  0.5*q(1),  0.5*q(0);
    return _output;
}

Eigen::MatrixXd task2::_H1(Eigen::VectorXd yin){
    Eigen::Vector4d q = yin.segment(0,4);
    Eigen::MatrixXd _output=Eigen::MatrixXd::Zero(3,7);

    _output.block(0,0,3,4) << +2*q(0), +2*q(0), +2*q(0), +2*q(0),
                              +2*q(0), +2*q(0), +2*q(0), +2*q(0),
                              +2*q(0), +2*q(0), +2*q(0), +2*q(0);
    return _output;
}

Eigen::MatrixXd task2::_H2(Eigen::VectorXd yin){
    Eigen::Vector4d q = yin.segment(0,4);
    Eigen::MatrixXd _output=Eigen::MatrixXd::Zero(3,7);

    _output.block(0,0,3,4) << +2*q(0), +2*q(0), +2*q(0), +2*q(0),
                              +2*q(0), +2*q(0), +2*q(0), +2*q(0),
                              +2*q(0), +2*q(0), +2*q(0), +2*q(0);
    return _output;
}

Eigen::MatrixXd task2::_H3(Eigen::VectorXd yin){
    Eigen::Vector4d q = yin.segment(0,4);
    Eigen::MatrixXd _output=Eigen::MatrixXd::Zero(3,7);

    _output.block(0,0,3,4) << +2*q(0), +2*q(0), +2*q(0), +2*q(0),
                              +2*q(0), +2*q(0), +2*q(0), +2*q(0),
                              +2*q(0), +2*q(0), +2*q(0), +2*q(0);
    return _output;
}

Eigen::Vector3d task2::_Zeta1(Eigen::VectorXd yin){
    Eigen::Vector4d q = yin.segment(0,4);
    Eigen::Vector3d _output(
            q(0)*q(0)+q(1)*q(1)-q(2)*q(2)-q(3)*q(3),
            +2*q(0)*q(3)+2*q(1)*q(2),
            -2*q(0)*q(2)-2*q(1)*q(3));
    return _output;
}

Eigen::Vector3d task2::_Zeta2(Eigen::VectorXd yin){
    Eigen::Vector4d q = yin.segment(0,4);
    Eigen::Vector3d _output(
            -2*q(0)*q(3)+2*q(1)*q(2),
            q(0)*q(0)-q(1)*q(1)+q(2)*q(2)-q(3)*q(3),
            +2*q(0)*q(1)-2*q(2)*q(3));
    return _output;
}

Eigen::Vector3d task2::_Zeta3(Eigen::VectorXd yin){
    Eigen::Vector4d q = yin.segment(0,4);
    Eigen::Vector3d _output(
            +2*q(0)*q(2)+2*q(1)*q(3),
            -2*q(0)*q(1)+2*q(2)*q(3),
            q(0)*q(0)-q(1)*q(1)-q(2)*q(2)+q(3)*q(3));
    return _output;
}
