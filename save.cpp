#include "save.hpp"
#include <iostream>
#include <fstream>

int savexy(Eigen::VectorXd xin, Eigen::VectorXd yin, std::string fname){
    int n=xin.rows();
    if (n != yin.rows()){
        std::cout<<"lenght of x and y have to be equal" << std::endl;
        return 1;
    }

    std::ofstream outfile;
    outfile.open(fname, std::ios::trunc);
    for(int i=0; i < n; i++){
        outfile << xin(i) << " " << yin(i) << "\n";
    }

    return 0;
}
