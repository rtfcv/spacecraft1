#!/usr/bin/env gnuplot
set term pdf enhanced size 12in, 6in
set output "omega.pdf"
plot "omega0_k1.dat" with line,\
 "omega1_k1.dat" with line,\
 "omega2_k1.dat" with line,\
 "omega0_k1_analytic.dat" with line,\
 "omega1_k1_analytic.dat" with line,\
 "omega2_k1_analytic.dat" with line
