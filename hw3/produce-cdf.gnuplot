set terminal postscript eps 26

set xlabel "Maximum file size (KB)"
set ylabel "Cumulative fraction of all files (%)"
set output "cdf.eps"
plot "transformed-results.txt" using 1:2 title "" with lines
