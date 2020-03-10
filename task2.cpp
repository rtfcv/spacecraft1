#include"header.h"
#include"headeronly.h"
#include<iostream>

int test2(){
	test::one();
	std::cout<<"2"<<" and pi is "<<pi<<std::endl;
	return 0;
}
