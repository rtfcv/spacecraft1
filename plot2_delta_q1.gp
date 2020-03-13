#!/usr/bin/env gnuplot
set xrange [0:100]
set yrange [0:0.1]
plot "task2_q1_delta.dat" using 1:(abs($2)) title "|{/Symbol D}q_1|" with lines,\
     "task2_P22.dat" title "{/Symbol \326}P_{22}" with steps,\
     "col_1.dat", "col_2.dat", "col_3.dat"
pause -1
