#!/bin/sh
read fname
mkdir $fname
gnuplot ./gnuplot_omega.gp
gnuplot ./gnuplot_q.gp
gnuplot ./gnuplot_delta_omega.gp
gnuplot ./gnuplot_delta_q.gp
mv *.pdf $fname/
cp param.ini $fname/
vim $fname/comment.txt
