#include <stdio.h>
#include <stdlib.h>

// Fungsi turunan (persamaan diferensial logistik)
double turunan_populasi(double populasi, double laju_pertumbuhan, double daya_dukung) {
    return laju_pertumbuhan * (1 - populasi/daya_dukung) * populasi;
}

int main() {
     printf("Program Dibuat Oleh Deandro Najwan Ahmad Syahbanna - 2306213174\n");
    // Parameter utama model
    double populasi = 2555.0;     // Populasi awal tahun 1950 (juta jiwa)
    double laju_pertumbuhan = 0.026;  // Tingkat pertumbuhan maksimum (per tahun)
    double daya_dukung = 12000.0;     // Kapasitas maksimum populasi (juta jiwa)
    
    // Rentang waktu simulasi
    int tahun_mulai = 1950;
    int tahun_akhir = 2000;
    double langkah_waktu = 1.0;  // Langkah tahunan
    
    // Data historis untuk validasi
    int tahun_hist[6] = {1950, 1960, 1970, 1980, 1990, 2000}; // array dibuat fix karena sesuai data yang ada tapi juga bisa dibuat dinamis apabila diperlukan di kemudian hari
    double pop_hist[6] = {2555, 3040, 3700, 4455, 5275, 6080};
    int jumlah_data = 6; // Jumlah data historis yang ada (1950-2000)

    // File untuk menyimpan hasil
    FILE *file_simulasi = fopen("hasil_data.txt", "w");
    if (file_simulasi == NULL) {
        fprintf(stderr, "Error opening file for simulation results.\n");
        return 1;
    }
       fprintf(file_simulasi, "Tahun\tPopulasi (juta)\n");
    FILE *file_aktual = fopen("data_awal.txt", "w");
    if (file_aktual == NULL) {
        fprintf(stderr, "Error opening file for historical data.\n");
        fclose(file_simulasi);
        return 1;
    }
    fprintf(file_aktual, "Tahun\tPopulasi (juta)\n");
    
    // Simpan data 
    for (int i = 0; i < jumlah_data; i++) {
        fprintf(file_aktual, "%d\t%.1f\n", tahun_hist[i], pop_hist[i]);
    }
    
    // Simulasi menggunakan Runge-Kutta Orde 4
    for (int tahun = tahun_mulai; tahun <= tahun_akhir; tahun++) {
        // Simpan hasil simulasi tahun ini
        fprintf(file_simulasi, "%d\t%.1f\n", tahun, populasi);
        
        // Hitung empat komponen Runge-Kutta
        double rk1 = turunan_populasi(populasi, laju_pertumbuhan, daya_dukung);
        double rk2 = turunan_populasi(populasi + 0.5 * langkah_waktu * rk1, laju_pertumbuhan, daya_dukung);
        double rk3 = turunan_populasi(populasi + 0.5 * langkah_waktu * rk2, laju_pertumbuhan, daya_dukung);
        double rk4 = turunan_populasi(populasi + langkah_waktu * rk3, laju_pertumbuhan, daya_dukung);
        
        // Hitung perubahan populasi
        double delta_p = (rk1 + 2*rk2 + 2*rk3 + rk4) * langkah_waktu / 6.0;
        
        // Perbarui populasi untuk tahun berikutnya
        populasi += delta_p;
    }
    
    // Tutup file data
    fclose(file_simulasi);
    fclose(file_aktual);
    
    // Buat script gnuplot untuk visualisasi
    FILE *plot_script = fopen("plot_populasi.gp", "w");
    fprintf(plot_script,
        "set terminal pngcairo size 800,600 enhanced font 'Verdana,12'\n"
        "set output 'perbandingan_populasi.png'\n\n"
        "set title 'Simulasi Pertumbuhan Penduduk Dunia (1950-2000)\\nMetode Runge-Kutta Orde 4'\n"
        "set xlabel 'Tahun'\n"
        "set ylabel 'Populasi (juta)'\n"
        "set grid\n"
        "set key left top\n\n"
        "set style line 1 lc rgb '#0060ad' lt 1 lw 2 pt 7 ps 0.5\n"
        "set style line 2 lc rgb '#dd181f' lt 1 lw 1.5\n\n"
        "plot 'hasil_data.txt' using 1:2 with linespoints ls 1 title 'Simulasi', \\\n"
        "     'data_awal.txt' using 1:2 with points pt 6 ps 1.5 lc rgb 'black' title 'Data Aktual'\n"
    );
    fclose(plot_script);
    system("gnuplot plot_populasi.gp");
    
    printf("Proses Selesai!!\n");

    
    return 0;
}