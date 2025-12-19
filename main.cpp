#include "tubes.h"

int main() {
    // Setup Struktur Data
    List daftarBarang;
    createList(daftarBarang);
    int globalIDCounter = 0;
    
    int pil;
    string username, pass;

    // Loop Utama Aplikasi
    while (true) {
        cout << "\n=== SISTEM LELANG ONLINE (DEV) ===\n";
        cout << "1. Login Admin\n";
        cout << "2. Login Penjual\n";
        cout << "3. Login Pembeli\n";
        cout << "4. Cari Barang (BST)\n";
        cout << "0. Keluar\n";
        cout << "Pilih: "; cin >> pil;

        if (pil == 0) break;

        if (pil == 1) {
            cout << "Password (ketik 'admin'): "; cin >> pass;
            if (pass == "admin") menuAdmin(daftarBarang);
            else cout << "Password Salah!\n";
        } 
        else if (pil == 2) {
            cout << "Username Penjual: "; cin >> username;
            menuPenjual(daftarBarang, username, globalIDCounter);
        } 
        else if (pil == 3) {
            cout << "Username Pembeli: "; cin >> username;
            menuPembeli(daftarBarang, username);
        }
        else if (pil == 4) {
            menuCariBarang(daftarBarang);
        }
        else {
            cout << "Input tidak valid.\n";
        }
    }

    cout << "Program Selesai.\n";
    return 0;
}