set terminal pngcairo size 1000,600 enhanced font 'Verdana,12'
set output 'simulasi_euler.png'

set title 'Simulasi Pertumbuhan Populasi dengan Metode Euler\nModel Logistik (1950-2000)'
set xlabel 'Tahun'
set ylabel 'Populasi (juta jiwa)'
set grid
set key left top

set style line 1 lc rgb '#dd181f' lt 1 lw 3
set style line 2 lc rgb '#000000' pt 7 ps 1.5

plot 'hasil_euler.txt' using 1:2 with lines ls 1 title 'Metode Euler', \
     'data_aktual.txt' using 1:2 with points ls 2 title 'Data Historis'
