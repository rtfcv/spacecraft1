#!/usr/bin/env gnuplot
set term pdf enhanced size 12in, 6in

set output "task2-q0.pdf"
set xrange [0:100]
plot "task2_q0_sim.dat" with lines title 'q_0 Estimated',\
     "task2_q0_env.dat" with lines title 'q_0 Actual',\
     "col_1.dat" using 1:2 title "col 1",\
     "col_2.dat" using 1:2 title "col 2",\
     "col_3.dat" using 1:2 title "col 3"

set output "task2-q1.pdf"
set xrange [0:100]
plot "task2_q1_sim.dat" with lines title 'q_1 Estimated',\
     "task2_q1_env.dat" with lines title 'q_1 Actual',\
     "col_1.dat" using 1:2 title "col 1",\
     "col_2.dat" using 1:2 title "col 2",\
     "col_3.dat" using 1:2 title "col 3"

set output "task2-q2.pdf"
set xrange [0:100]
plot "task2_q2_sim.dat" with lines title 'q_2 Estimated',\
     "task2_q2_env.dat" with lines title 'q_2 Actual',\
     "col_1.dat" using 1:2 title "col 1",\
     "col_2.dat" using 1:2 title "col 2",\
     "col_3.dat" using 1:2 title "col 3"

set output "task2-q3.pdf"
set xrange [0:100]
plot "task2_q3_sim.dat" with lines title 'q_3 Estimated',\
     "task2_q3_env.dat" with lines title 'q_3 Actual',\
     "col_1.dat" using 1:2 title "col 1",\
     "col_2.dat" using 1:2 title "col 2",\
     "col_3.dat" using 1:2 title "col 3"
