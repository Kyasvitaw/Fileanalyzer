set terminal png
set output "words.png"

set title "Words per File"
set xlabel "Files"
set ylabel "Number of Words"

set style data histograms
set style fill solid
set boxwidth 0.5

set xtics rotate by -45

plot "words.txt" using 2:xtic(1) title "Words"
