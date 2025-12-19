#include "tubes.h"

int main() {
    // 1. Setup Struktur Data
    List daftarBarang;
    createList(daftarBarang);
    
    // Counter ID agar setiap barang punya ID unik (1, 2, 3...)
    int globalIDCounter = 1; 
    
    int pil;
    string username, pass;

    // 2. Loop Utama Aplikasi
    while (true) {
        // Bersihkan layar terminal biar rapi (Opsional, kalau error hapus aja)
        // system("cls"); 

        cout << "\n=== SISTEM LELANG ONLINE (DEV) ===\n";
        cout << "1. Login Admin\n";
        cout << "2. Login Penjual (TUGAS KAMU)\n";
        cout << "3. Login Pembeli\n";
        cout << "4. Cari Barang\n";
        cout << "0. Keluar\n";
        cout << "Pilih: "; cin >> pil;

        if (pil == 0) {
            cout << "Program Selesai. Terima kasih!\n";
            break;
        }

        if (pil == 1) {
            cout << "Password (ketik 'admin'): "; cin >> pass;
            if (pass == "admin") {
                menuAdmin(daftarBarang);
            } else {
                cout << "Password Salah!\n";
            }
        } 
        else if (pil == 2) {
            cout << "Masukkan Username Penjual: "; cin >> username;
            // Masuk ke menu buatanmu di tubes.cpp
            menuPenjual(daftarBarang, username, globalIDCounter);
        } 
        else if (pil == 3) {
            cout << "Masukkan Username Pembeli: "; cin >> username;
            menuPembeli(daftarBarang, username);
        }
        else if (pil == 4) {
            menuCariBarang(daftarBarang);
        }
        else {
            cout << "Input tidak valid.\n";
        }
    }

    return 0;
}