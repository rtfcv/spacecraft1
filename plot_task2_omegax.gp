#!/usr/bin/env gnuplot
plot "task2_omegax_sim.dat" with lines, "task2_omegax_env.dat" with lines, "task2_P44.dat" with steps
#plot "task2_omegay_sim.dat" with lines, "task2_omegay_env.dat" with lines, "task2_P55.dat" with steps
#plot "task2_q1_sim.dat" with lines, "task2_q1_env.dat" with lines, "task2_P11.dat" with steps
#plot "task2_q2_sim.dat" with lines, "task2_q2_env.dat" with lines, "task2_P22.dat" with steps
# plot "task2_omegax_env.dat"
pause -1
