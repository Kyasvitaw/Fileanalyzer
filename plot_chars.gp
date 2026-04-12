set terminal png
set output "chars.png"

set title "Characters per File"
set xlabel "Files"
set ylabel "Number of Characters"

set style data histograms
set style fill solid
set boxwidth 0.5

set xtics rotate by -45

plot "chars.txt" using 2:xtic(1) title "Chars"
