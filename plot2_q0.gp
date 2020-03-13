#!/usr/bin/env gnuplot
plot "task2_q0_env.dat" with lines title 'q_0 Actual',\
     "task2_q0_sim.dat" with lines title 'q_0 Estimated'
pause -1
