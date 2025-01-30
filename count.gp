set datafile separator ','
set xlabel 'Character'
set ylabel 'Count'
set ytics 1
set style data histogram
set style histogram clustered gap 1
set boxwidth 0.9
set style fill solid border -1
plot 'counts.csv' using 2:xticlabels(1) with boxes title 'Character Counts'
