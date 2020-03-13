#!/usr/bin/env gnuplot
set term pdf enhanced size 12in, 6in

set output "task2-q0-delta.pdf"
set xrange [0:100]
set yrange [0:0.1]
plot "task2_q0_delta.dat" using 1:(abs($2)) title "|{/Symbol D}q_0|(=x_1)" with lines,\
     "task2_P11.dat" title "{/Symbol \326}P_{11}" with steps,\
     "col_1.dat" using 1:2 title "col 1",\
     "col_2.dat" using 1:2 title "col 2",\
     "col_3.dat" using 1:2 title "col 3"

set output "task2-q1-delta.pdf"
set xrange [0:100]
set yrange [0:0.1]
plot "task2_q1_delta.dat" using 1:(abs($2)) title "|{/Symbol D}q_1|(=x_2)" with lines,\
     "task2_P22.dat" title "{/Symbol \326}P_{22}" with steps,\
     "col_1.dat" using 1:2 title "col 1",\
     "col_2.dat" using 1:2 title "col 2",\
     "col_3.dat" using 1:2 title "col 3"

set output "task2-q2-delta.pdf"
set xrange [0:100]
set yrange [0:0.1]
plot "task2_q2_delta.dat" using 1:(abs($2)) title "|{/Symbol D}q_2|(=x_3)" with lines,\
     "task2_P33.dat" title "{/Symbol \326}P_{33}" with steps,\
     "col_1.dat" using 1:2 title "col 1",\
     "col_2.dat" using 1:2 title "col 2",\
     "col_3.dat" using 1:2 title "col 3"

set output "task2-q3-delta.pdf"
set xrange [0:100]
set yrange [0:0.1]
plot "task2_q3_delta.dat" using 1:(abs($2)) title "|{/Symbol D}q_3|(=x_4)" with lines,\
     "task2_P44.dat" title "{/Symbol \326}P_{44}" with steps,\
     "col_1.dat" using 1:2 title "col 1",\
     "col_2.dat" using 1:2 title "col 2",\
     "col_3.dat" using 1:2 title "col 3"
