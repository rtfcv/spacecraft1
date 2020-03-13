#!/usr/bin/env gnuplot
plot "task2_q0_delta.dat" using 1:(abs($2)) title "|{/Symbol D}q_0|" with lines,\
     "task2_P11.dat" title "{/Symbol \326}P_{11}" with steps,\
     "col_1.dat", "col_2.dat", "col_3.dat"
pause -1
