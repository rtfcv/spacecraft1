#!/usr/bin/env gnuplot
plot "task2_omegax_delta.dat" using 1:(abs($2)) title "|{/Symbol D}{/Symbol w}_x|" with lines,\
     "task2_P55.dat" title "{/Symbol \326}P_{44}" with steps,\
     "col_1.dat","col_2.dat","col_3.dat"
pause -1
