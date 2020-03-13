#/usr/bin/env/gnuplot
plot "task2_omegaz_delta.dat" using 1:(abs($2)) title "|{/Symbol D}{/Symbol w}_z|" with lines,\
     "task2_P77.dat" title "{/Symbol \326}P_{77}" with steps
     "col_1.dat", "col_2.dat", "col_3.dat"
pause -1
