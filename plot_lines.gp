set terminal png
set output "lines.png"

set title "Lines per File"
set xlabel "Files"
set ylabel "Number of Lines"

set style data histograms
set style fill solid
set boxwidth 0.5

set xtics rotate by -45

plot "lines.csv" using 2:xtic(1) title "Lines"
