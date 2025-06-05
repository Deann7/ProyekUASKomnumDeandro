#include <stdio.h>
#include <stdlib.h>

// Fungsi turunan (persamaan diferensial logistik)
double turunan_populasi(double populasi, double laju_pertumbuhan, double daya_dukung) {
    return laju_pertumbuhan * (1 - populasi/daya_dukung) * populasi;
}

int main() {
    printf("Program Simulasi Populasi dengan Metode Euler\n");
    printf("Dibuat Oleh Deandro Najwan Ahmad Syahbanna - 2306213174\n\n");

    // Parameter model
    double populasi = 2555.0;     // Populasi awal tahun 1950 (juta jiwa)
    double laju_pertumbuhan = 0.026;  // Tingkat pertumbuhan maksimum (per tahun)
    double daya_dukung = 12000.0;     // Kapasitas maksimum populasi (juta jiwa)
    
    // Rentang waktu simulasi
    int tahun_mulai = 1950;
    int tahun_akhir = 2000;
    double langkah_waktu = 1.0;  // Langkah tahunan
    
    // Data historis untuk validasi
    int tahun_hist[6] = {1950, 1960, 1970, 1980, 1990, 2000};
    double pop_hist[6] = {2555, 3040, 3700, 4455, 5275, 6080};

    // File output
    FILE *file_euler = fopen("hasil_euler.txt", "w");
    FILE *file_aktual = fopen("data_aktual.txt", "w");
    
    // Header file
    fprintf(file_euler, "Tahun\tPopulasi (juta)\n");
    fprintf(file_aktual, "Tahun\tPopulasi (juta)\n");
    
    // Simpan data historis
    for (int i = 0; i < 6; i++) {
        fprintf(file_aktual, "%d\t%.1f\n", tahun_hist[i], pop_hist[i]);
    }
    
    printf("Menjalankan simulasi Metode Euler...\n");
    
    // Simulasi dengan Metode Euler
    for (int tahun = tahun_mulai; tahun <= tahun_akhir; tahun++) {
        fprintf(file_euler, "%d\t%.1f\n", tahun, populasi);
        
        // Tampilkan progress setiap 10 tahun
        if ((tahun - tahun_mulai) % 10 == 0) {
            printf("Tahun %d: %.1f juta jiwa\n", tahun, populasi);
        }
        
        // Hitung perubahan populasi (Euler sederhana)
        double delta_p = turunan_populasi(populasi, laju_pertumbuhan, daya_dukung) * langkah_waktu;
        
        // Update populasi
        populasi += delta_p;
    }
    
    fclose(file_euler);
    fclose(file_aktual);
      // Visualisasi dengan Gnuplot - fokus pada Metode Euler
    FILE *plot_script = fopen("plot_euler.gp", "w");
    fprintf(plot_script,
        "set terminal pngcairo size 1000,600 enhanced font 'Verdana,12'\n"
        "set output 'simulasi_euler.png'\n\n"
        "set title 'Simulasi Pertumbuhan Populasi dengan Metode Euler\\nModel Logistik (1950-2000)'\n"
        "set xlabel 'Tahun'\n"
        "set ylabel 'Populasi (juta jiwa)'\n"
        "set grid\n"
        "set key left top\n\n"
        "set style line 1 lc rgb '#dd181f' lt 1 lw 3\n"
        "set style line 2 lc rgb '#000000' pt 7 ps 1.5\n\n"
        "plot 'hasil_euler.txt' using 1:2 with lines ls 1 title 'Metode Euler', \\\n"
        "     'data_aktual.txt' using 1:2 with points ls 2 title 'Data Historis'\n"
    );
    fclose(plot_script);
    
    printf("\nMembuat grafik...\n");
    system("gnuplot plot_euler.gp");
    
    printf("\nSimulasi Metode Euler selesai!\n");
    printf("=================================\n");
    printf("File yang dihasilkan:\n");
    printf("- Data simulasi Euler: hasil_euler.txt\n");
    printf("- Data historis: data_aktual.txt\n");
    printf("- Grafik simulasi: simulasi_euler.png\n");
    printf("- Script Gnuplot: plot_euler.gp\n");
    
    // Tampilkan ringkasan hasil
    printf("\nRingkasan Hasil Simulasi:\n");
    printf("- Populasi awal (1950): %.1f juta jiwa\n", 2555.0);
    printf("- Populasi akhir (2000): %.1f juta jiwa\n", populasi);
    printf("- Laju pertumbuhan: %.3f per tahun\n", laju_pertumbuhan);
    printf("- Daya dukung: %.1f juta jiwa\n", daya_dukung);
    
    return 0;
}