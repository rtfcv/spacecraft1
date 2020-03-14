#ifndef _MYUNITS_H_
#define _MYUNITS_H_
#include <cmath>
namespace my{
	namespace Units{
		namespace metric{
			//define the base constants
			#ifndef MY_METER
				#define MY_METER 1.0
			#endif
			#ifndef MY_KILOGRAM
				#define MY_KILOGRAM 1.0
			#endif
			#ifndef MY_SECOND
				#define MY_SECOND 1.0
			#endif
			#ifndef MY_G_METRIC
				#define MY_G_METRIC 9.8;
			#endif
			//the holy trinity
			const double m=MY_METER;
			const double kg=MY_KILOGRAM;
			const double sec=MY_SECOND;

			//define prefixes
			const double MILI=10e-03;
			const double KILO=10e+03;
			const double MEGA=10e+06;

			//define mass
			const double gram=MILI*kg;
			const double ton=KILO*kg;
			const double slug=14.59390*kg;

			//define length
			const double km=KILO*m;
			const double mm=MILI*m;
			const double cm=0.01*m;
			const double nm=1852.0*m;
			const double ft=0.3048*m;
			const double inch=0.0254*m;

			//define time;
			const double ms=MILI*sec;
			const double min=60.0*sec;
			const double hr=60*min;
			const double days=24.0*hr;

			//define speed
			const double kn=nm/hr;
			const double kt=kn;

			//define force
			const double G=MY_G_METRIC;
			const double N=kg*m/sec/sec;
			const double kN=KILO*N;
			const double MN=MEGA*N;
			const double kgf=kg*G;
			const double lb=4.44822;
			const double kips=KILO*lb;

			//define pressure
			const double Pa=N/m/m;
			const double hPa=100.0*Pa;
			const double MPa=MEGA*Pa;
			const double psi=lb/inch/inch;
			const double ksi=KILO*psi;

			//define angles
			const double pi=std::acos(-1);
			const double rad=1;
			const double deg=pi/180.0;
/*
			//define workrate
			const double W;

			const double PS;


			const double J;
			const double kJ;


			//define
			const double sth; 
*/
		}
	}
}
#endif
