set terminal pngcairo size 800,600 enhanced font 'Verdana,12'
set output 'perbandingan_populasi.png'

set title 'Simulasi Pertumbuhan Penduduk Dunia (1950-2000)\nMetode Runge-Kutta Orde 4'
set xlabel 'Tahun'
set ylabel 'Populasi (juta)'
set grid
set key left top

set style line 1 lc rgb '#0060ad' lt 1 lw 2 pt 7 ps 0.5
set style line 2 lc rgb '#dd181f' lt 1 lw 1.5

plot 'hasil_data.txt' using 1:2 with linespoints ls 1 title 'Simulasi', \
     'data_awal.txt' using 1:2 with points pt 6 ps 1.5 lc rgb 'black' title 'Data Aktual'
