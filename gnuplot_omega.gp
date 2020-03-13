#!/usr/bin/env gnuplot
set term pdf enhanced size 12in, 6in
set output "task2-omegax.pdf"
set xrange[0:100]
plot "task2_omegax_sim.dat" with lines title '{/Symbol w}_x Estimated',\
     "task2_omegax_env.dat" with lines title '{/Symbol w}_x Actual',\
     "col_1.dat" using 1:2 title "col 1",\
     "col_2.dat" using 1:2 title "col 2",\
     "col_3.dat" using 1:2 title "col 3"

set output "task2-omegay.pdf"
set xrange[0:100]
plot "task2_omegay_sim.dat" with lines title '{/Symbol w}_y Estimated',\
     "task2_omegay_env.dat" with lines title '{/Symbol w}_y Actual',\
     "col_1.dat" using 1:($2+1.5) title "col 1",\
     "col_2.dat" using 1:($2+1.5) title "col 2",\
     "col_3.dat" using 1:($2+1.5) title "col 3"

set output "task2-omegaz.pdf"
set xrange[0:100]
plot "task2_omegaz_sim.dat" with lines title '{/Symbol w}_z Estimated',\
     "task2_omegaz_env.dat" with lines title '{/Symbol w}_z Actual',\
     "col_1.dat" using 1:2 title "col 1",\
     "col_2.dat" using 1:2 title "col 2",\
     "col_3.dat" using 1:2 title "col 3"
