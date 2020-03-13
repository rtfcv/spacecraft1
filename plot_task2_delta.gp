# plot "task2_q1_delta.dat" using 1:(abs($2)) title "q_1" with lines,\
#      "task2_P11.dat" title "{/Symbol \326}P_{11}" with steps
plot "task2_q2_delta.dat" using 1:(abs($2)) title "q_2" with lines,\
     "task2_P22.dat" title "{/Symbol \326}P_{22}" with steps
# plot "task2_omegax_delta.dat" using 1:(abs($2)) title "|{/Symbol D}{/Symbol w}_x|" with lines,\
#      "task2_P44.dat" title "{/Symbol \326}P_{44}" with steps
pause -1
