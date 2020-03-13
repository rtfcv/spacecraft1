#/usr/bin/env/gnuplot
plot "task2_omegay_delta.dat" using 1:(abs($2)) title "|{/Symbol D}{/Symbol w}_y|" with lines,\
     "task2_P66.dat" title "{/Symbol \326}P_{66}" with steps,\
     "col_1.dat", "col_2.dat", "col_3.dat"
pause -1
