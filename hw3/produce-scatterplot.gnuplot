set terminal postscript eps 26

set xlabel "Rank"
set ylabel "Size (Bytes)"
set xrange [0:100]
set output "scatterplot.eps"
plot "results.txt" using 1:3 title "" with points

