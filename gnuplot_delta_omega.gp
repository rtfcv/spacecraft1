#!/usr/bin/env gnuplot
set term pdf enhanced size 12in, 6in

set output "task2-omegax-delta.pdf"
set xrange [0:100]
set yrange [0:0.1]
plot "task2_omegax_delta.dat" using 1:(abs($2)) title "|{/Symbol D}{/Symbol w}_x|(=x_5)" with lines,\
     "task2_P55.dat" title "{/Symbol \326}P_{66}" with steps,\
     "col_1.dat" using 1:2 title "col 1",\
     "col_2.dat" using 1:2 title "col 2",\
     "col_3.dat" using 1:2 title "col 3"

set output "task2-omegay-delta.pdf"
set xrange [0:100]
set yrange [0:0.1]
plot "task2_omegay_delta.dat" using 1:(abs($2)) title "|{/Symbol D}{/Symbol w}_y|(=x_6)" with lines,\
     "task2_P66.dat" title "{/Symbol \326}P_{66}" with steps,\
     "col_1.dat" using 1:2 title "col 1",\
     "col_2.dat" using 1:2 title "col 2",\
     "col_3.dat" using 1:2 title "col 3"

set output "task2-omegaz-delta.pdf"
set xrange [0:100]
set yrange [0:0.1]
plot "task2_omegaz_delta.dat" using 1:(abs($2)) title "|{/Symbol D}{/Symbol w}_y|(=x_7)" with lines,\
     "task2_P77.dat" title "{/Symbol \326}P_{77}" with steps,\
     "col_1.dat" using 1:2 title "col 1",\
     "col_2.dat" using 1:2 title "col 2",\
     "col_3.dat" using 1:2 title "col 3"
