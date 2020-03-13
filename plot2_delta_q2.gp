#!/usr/bin/env gnuplot
plot "task2_q2_delta.dat" using 1:(abs($2)) title "|{/Symbol D}q_2|" with lines,\
     "task2_P33.dat" title "{/Symbol \326}P_{33}" with steps,\
     "col_1.dat", "col_2.dat", "col_3.dat"
pause -1
