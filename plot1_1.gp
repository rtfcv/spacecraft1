#!/usr/bin/env gnuplot
set term pdf enhanced size 12in, 6in
set output "y.pdf"
plot "q0_k1.dat" with line title 'q_0',\
     "q1_k1.dat" with line title 'q_1',\
     "q2_k1.dat" with line title 'q_2',\
     "q3_k1.dat" with line title 'q_3',\
     "omega0_k1.dat" with line title '{/Symbol w}_x',\
     "omega1_k1.dat" with line title '{/Symbol w}_y',\
     "omega2_k1.dat" with line title '{/Symbol w}_z'
