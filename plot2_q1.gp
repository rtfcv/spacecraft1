#!/usr/bin/env gnuplot
plot "task2_q1_env.dat" with lines title 'q_1 Actual',\
     "task2_q1_sim.dat" with lines title 'q_1 Estimated'
pause -1
