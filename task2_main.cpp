#include <iostream>
#include "headeronly.h"
#include "header.h"

int main(){
    test::one();
    std::cout << std::endl;
    test2();
    std::cout << pi;
}
