#ifndef _MYTIMER_H
#define _MYTIMER_H

#include <iostream>
#include <cmath>
#include <chrono>

namespace my{
	class timer
	{
		std::chrono::system_clock::time_point  _start, _end; 
	public:
		int start(){
			_start = std::chrono::system_clock::now();
			return 0;
		}
		int end(){
			_end = std::chrono::system_clock::now();
			double elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(_end-_start).count();
			int min=std::floor(elapsed/1000/60);
			double sec=elapsed/1000-60*min;
			std::cout<<"took "<<min<<"min "<<sec<<"secs\n";
			return 0;
		}
		timer(){
		}
	};
}
#endif
