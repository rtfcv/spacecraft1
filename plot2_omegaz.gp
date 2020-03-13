#!/usr/bin/env gnuplot
plot "task2_omegaz_sim.dat" with lines title "{/Symbol w}_z Actual",\
    "task2_omegaz_env.dat" with lines title "{/Symbol w}_z Estimated"
pause -1
