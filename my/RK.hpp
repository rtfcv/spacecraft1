#ifndef MYRK_H
#define MYRK_H

#include <iostream>
#include <cmath>
#include <Eigen/Dense>
#include <functional>
namespace my{
class RK{
    bool _Jexists=false;
    bool _Fexists=false;

    std::function<Eigen::VectorXd(double, Eigen::VectorXd)> f;
    std::function<Eigen::MatrixXd(double, Eigen::VectorXd)> Jf;
    //////////////////////////////////////////////////////////////////////////
    const double rt3 = std::sqrt(3);
    int _n;
    double _h=0.0001;
    double _prec = 0.001;
    Eigen::Vector4d _c4;
    Eigen::Vector4d _b4;
    Eigen::Matrix4d _A4;

    Eigen::Vector2d _cgl4;
    Eigen::Vector2d _bgl41;
    Eigen::Vector2d _bgl42;
    Eigen::Matrix2d _Agl4;

    public:
        int setpresc(){
            //configure all the variables
            return 0;
        }

        int seth(double hin){_h=hin;return 0;}

        Eigen::MatrixXd rk4_steps(Eigen::VectorXd r0, double t0 , int steps){
            double h = _h;

            if( steps < 1.0){
                //std::cout<<steps<<std::endl;
                return r0;}//just check this before doing anything            

            //rename variables to make things easier.
            int s=4;
            _n=r0.rows(); //decide dimensions now
            int n=_n;
            Eigen::Vector4d c=_c4;
            Eigen::Vector4d b=_b4;
            Eigen::Matrix4d A=_A4;

            Eigen::MatrixXd K(n, s);
            Eigen::MatrixXd outPut(n, steps+1);
            outPut.col(0)=r0;

            //variables for runge kutta steps
            double t1 = t0;
            Eigen::VectorXd rn1 = r0;//initial conditions
            double t2 = t0;
            Eigen::VectorXd rn2 = r0;
            Eigen::VectorXd dr = r0*0;
            Eigen::MatrixXd Kt(s, n);

            int stepsDone=0;

//            for(int m=0; m<=steps+1; m++){//runge kutta loop
            while(true){
                //if(h > t-t2){h=t-t2;}//modify the final h to fit the t given.
                
                t1=t2;
                rn1=rn2;
                
                for(int j=0;j<s;j++){    //calculate R here
                    Kt=K.transpose();                    
                    dr=h*A.row(j)*Kt;
                    K.col(j)=f(t1+c(j)*h, rn1+dr);
                }
                t2=t1+h;
                rn2=rn1+h*K*b;

                stepsDone+=1;
                outPut.col(stepsDone) = rn2;

                if(stepsDone>=steps){break;}
            }

            return outPut;
        }

        Eigen::VectorXd gl2(double t, double t0, Eigen::VectorXd r0){//The Gauss–Legendre method of order four
            double h = _h;
            double steps = (t-t0)/h;
            if( steps < 1.0){
                //std::cout<<steps<<std::endl;
                return r0;}//just check this before doing anything            
            
            //rename variables to make things easier.
            int s=2;
            int n=_n;
            Eigen::Vector2d c=_cgl4;
            Eigen::Vector2d b=_bgl41;
            Eigen::Vector2d b2=_bgl42;
            Eigen::Matrix2d A=_Agl4;

            Eigen::MatrixXd K(n, s);
            //variables for newton iterations
            int cnt=0;
            Eigen::MatrixXd K0(n, s);
            Eigen::MatrixXd Kn1(n, s);
            Eigen::MatrixXd Kn1t(s, n);
            Eigen::MatrixXd Kn2(n, s);
            Eigen::VectorXd kn1 = Eigen::VectorXd::Zero(n*s); //matrix(n,s) ith row jth collum is k((i-1)*s+(j-1)) this means k_j of ith variable.
            Eigen::VectorXd kn2 = Eigen::VectorXd::Zero(n*s); //matrix(n,s) ith row jth collum is k((i-1)*s+(j-1)) this means k_j of ith variable.                            
            Eigen::VectorXd g = Eigen::VectorXd::Ones(n*s); //just a vector containing everything from G
            Eigen::MatrixXd G(n,s);
            Eigen::MatrixXd Jg(n*s, n*s);
            Eigen::VectorXd z = Eigen::VectorXd::Zero(n*s); //z={Jg}^{-1}*g
            //temporary vectors to hold value
            Eigen::VectorXd tempf = Eigen::VectorXd::Zero(n);

            //variables for runge kutta steps
            double t1 = t0;
            Eigen::VectorXd rn1 = r0;//initial conditions
            double t2 = t0;
            Eigen::VectorXd rn2 = r0;
            Eigen::VectorXd dr = 0*r0;
            
            //preparation for solution for K/////////////////////////////////////////////////////////////// 
            //here we calculate initial value of K, which is Kn1, for the newton method, using assumption K0ij ~ fi(t0,r0)
            tempf=f(t0, r0);
            for(int i=0;i<n;i++){
                K0.row(i) = tempf(i)*Eigen::VectorXd::Ones(s);//this is the initial value for the newton loop
            }
            /*
            also we think of vector $ k_{s(p-1)+p}=K_{pq} $\\
            then we define vector $ g_{s(i-1)+j}=G_{ij} $
            where \[
            G_{ij}=K_{ij}-f_i[ t+c_j, r_1 + h A.row(j).dot(K.row(1)), r_2 ... ]
            \]
            here we calculate initial (and only) value for Jacobi matrix of$ \vec(g) $(as we would like to call it Jg) for the simplified Newton Method;\[
            \frac{\partial G_{ij}}{\partial K_{lm}} = \delta_{il}\delta_{jn} - \frac{\partial f_i}{\partial r_l}\frac{\partial r_l}{\partial K_{lm}}
            = \delta_{il}\delta_{jn} - hA_{jm}\frac{\partial f_i}{\partial r_l}
            \]where\[
            \frac{\partial r_l}{\partial K_{lm}}=hA_{jm}
            \]
            we should have Jacobi of f given to us as Jf so we can substitute$ \frac{\partial f_i}{\partial r_l} $ with $ {Jf}_{il} $
            FYI\[
            {Jg}_{(s(i-1)+j)(s(l-1)+m)}=\frac{\partial g_{s(i-1)+j}}{\partial k_{l(s-1)+m}} = \frac{\partial G_{ij}}{\partial K_{lm}}
            \]
            now we implement it in a simplified form like this:
            */
            Eigen::MatrixXd tempJf = Jf(t0, r0);
            Eigen::MatrixXd At = A.transpose();
            Eigen::MatrixXd In= Eigen::MatrixXd::Identity(s,s);//as the name suggests.
            /*//this was for the simplified newton method
            for(int i=0;i<n;i++){for(int l=0;l<n;l++){//this loop calculates Jg
                Jg.block(s*i,s*l,s,s) = (i==l)*In - h*tempJf(i,l)*At;
            }}
            Eigen::FullPivLU< Eigen::MatrixXd > lu(Jg);//do the LU decompositions for later
            */
//            for(int m=0; m<steps+1; m++){//runge kutta loop
            while(true){
                rn1=rn2;//initialize for the runke kutta loop.
                t1=t2;
                if(h > t-t2){h=t-t2;}//modify the final h to fit the t given.
                /*
                calculate K for mth step using newton method.
                we want to do something like this: $ \vec{k}_{p+1}=\vec{k}_{p} +{Jg}^{-1}\vec{g}(k_p) $
                but calculating$ {Jg}^{-1} $ is kinda costly.
                so we make L and U so that $ LU = Jg$
                Luckily we have already done that as lu.
                now we solve this situations
                remember we want to solve the equasion that looks like this\[
                LU{Jg}^{-1}\vec{g}(k_p)={Jg}z=\vec{g}(k_p)
                \]but before that we have to calculate $\vec{g}(k_p)$ which looks like this\{
                G.col(j)=K_p.col(j)-\vec{f}[ t+c_j, r_{n,1} + h A.row(j).dot(K_p.row(1)), r_{n,2} ... ]
                =K_p.col(j)-\vec{f}[ t+c_j; \vec{r}_n+A.row(j){K_p}^T]
                \]
                */
                tempf=f(t1, rn1);
                for(int i=0;i<n;i++){
                    Kn2.row(i) = tempf(i)*Eigen::VectorXd::Ones(s);//initial value for the Newton loop//////////////////////////
                }
                cnt=0;
                /////////////////////////////////////////////////////////////////////////////////
                //calculate the Jacobian
                tempJf = Jf(t1, rn1);
                for(int i=0;i<n;i++){for(int l=0;l<n;l++){//this loop calculates Jg
                    Jg.block(s*i,s*l,s,s) = (i==l)*In - h*tempJf(i,l)*At;
                }}
                Eigen::FullPivLU< Eigen::MatrixXd > lu(Jg);//do the LU decompositions for later
                /////////////////////////////////////////////////////////////////////////////////
                while(true){//this loops the Newton method.
                    //the step before has finished            
                    if (cnt > 9999){std::cerr<<"did not converge after "<<cnt<<" iterations\n";break;}                    
                    cnt++;
                    Kn1=Kn2;
                    Kn1t = Kn1.transpose();

                    for(int j=0;j<s;j++){ 
                        Eigen::VectorXd tempr = h*A.row(j)*Kn1t;
                        G.col(j) = Kn1.col(j)- f( t1+h*c(j), rn1+tempr);
                    }//this loop calculates $\vec{g}(k_p)$
                    for(int i=0;i<n;i++){g.segment(s*i,s)=G.row(i);}//convert G to g (hint G.row(i) is g(i,...,i+s) )
                    if(g.squaredNorm() < h*h){break;}//convergence check

                    for(int i=0;i<n;i++){kn1.segment(s*i,s)=Kn1.row(i);}//convert Kn1 to kn1 (hint Kn1.row(i) is kn1(i,...,i+s) )
                    /////////////////////////////////////////////////////////////////////////////////
                    //calculate the Jacobian
                    dr=h*Kn1*b;
                    tempJf = Jf(t1, rn1+dr);
                    for(int i=0;i<n;i++){for(int l=0;l<n;l++){//this loop calculates Jg
                        Jg.block(s*i,s*l,s,s) = (i==l)*In - h*tempJf(i,l)*At;
                    }}
                    Eigen::FullPivLU<Eigen::MatrixXd> lu(Jg);//do the LU decompositions
                    //////////////////////////////////////////////////////////////////////////////////
                    z=lu.solve(g);
                    kn2=kn1-z;//k_{n+1}= k_{n}+{Jg}^{-1}g
                    for(int i=0;i<n;i++){Kn2.row(i)=kn2.segment(s*i,s);}//convert kn2 to Kn2 (hint Kn2.row(i) is kn2(i,...,i+s) )
                }

                K=Kn2;//rename it to make it clear that this is the result.
                //now that we have K we calculate the \vec{y} for the {m+1}th step.
                t2=t1+h;
                rn2=rn1+h*K*b;
                if(t2>=t){break;}
            }
            return rn2;
        }

        int _init(){
            _n=6;//should actually be decided according to the dimention of y
            _A4<<    0,  0,  0,  0,
                     0.5,0,  0,  0,
                     0,  0.5,0,  0,
                     0,  0,1.0,  0;
            _c4<< 0,0.5,0.5,1;
            _b4<< 1.0/3,1.0/6,1.0/6,1.0/3;

            _cgl4<<0.5*(1-1/rt3), 0.5*(1-1/rt3);
            _bgl41<<0.5, 0.5;
            _bgl42<<0.5*(1+rt3), 0.5*(1-rt3);
            _Agl4<<    0.25,         0.25-0.5/rt3,
                       0.25+0.5/rt3, 0.25;

            return 0;
        }

        int set_func(std::function<Eigen::VectorXd(double, Eigen::VectorXd)> fin){
            std::cout<<"function set"<<std::endl;
            f=fin;
            _Fexists=true;
            return 0;
        }

        //the constructor when nothing is given in the beggining
        RK(){
            _Fexists=false;
            _Jexists=false;
            _init();
        }

        //the constructor when Jacobian was NOT provided
        RK(std::function<Eigen::VectorXd(double, Eigen::VectorXd)> fin){
            f=fin;
            _Fexists=true;
            _Jexists=false;
            _init();
        }

        //the constructor when Jacobian WAS provided
        RK(std::function<Eigen::VectorXd(double, Eigen::VectorXd)> fin,
                std::function<Eigen::MatrixXd(double, Eigen::VectorXd)> Jfin){
            f=fin;
            Jf=Jfin;
            _Fexists=true;
            _Jexists=true;
            _init();
        }
};
}
#endif

