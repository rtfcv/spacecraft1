#!/usr/bin/env gnuplot
plot "task2_omegax_sim.dat" with lines title '{/Symbol w}_x Actual',\
     "task2_omegax_env.dat" with lines title '{/Symbol w}_x Estimated',\
     "col_1.dat", "col_2.dat", "col_3.dat"
pause -1
