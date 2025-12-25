#include "tubes.h"

int main() {
    // 1. Setup Data Barang & User
    List daftarBarang;
    createList(daftarBarang);
    
    ListUser dataUser; // Wadah akun
    createUserList(dataUser);

    int globalIDCounter = 0;
    
    // Load Data
    loadFromFile(daftarBarang, globalIDCounter);
    loadUsers(dataUser); // Load akun user

    int pilAwal, pilLogin;
    string uName, pass, role;

    while (true) {
        system("cls"); // Bersihkan layar (Windows)
        cout << "\n=== SELAMAT DATANG DI LELANG ONLINE ===\n";
        cout << "1. Login\n";
        cout << "2. Register Akun Baru\n";
        cout << "0. Keluar\n";
        cout << "Pilih: "; cin >> pilAwal;

        if (pilAwal == 0) {
            saveToFile(daftarBarang);
            saveUsers(dataUser);
            break;
        }

        if (pilAwal == 1) { // --- MENU LOGIN ---
            cout << "\n--- PILIH ROLE LOGIN ---\n";
            cout << "1. Admin\n";
            cout << "2. Penjual\n";
            cout << "3. Pembeli\n";
            cout << "Pilih: "; cin >> pilLogin;

           if (pilLogin == 1) {
                // LOGIN ADMIN
                cout << "Username: "; cin >> uName;
                cout << "Password: "; cin >> pass;
                
                if (uName == "admin" && isPasswordValid(pass) && pass == "admin12345") {
                    menuAdmin(daftarBarang);
                } else {
                    cout << ">> Login Gagal! Cek Username/Password.\n";
                }

            

            } else if (pilLogin == 2) {
                // LOGIN PENJUAL
                cout << "Username: "; cin >> uName;
                cout << "Password (Minimal 8 angka): "; cin >> pass;
                if (loginUser(dataUser, uName, pass, "penjual")) {
                    menuPenjual(daftarBarang, uName, globalIDCounter);
                } else {
                    cout << ">> Gagal! Akun tidak ditemukan atau salah password.\n";
                }

            } else if (pilLogin == 3) {
                // LOGIN PEMBELI
                cout << "Username: "; cin >> uName;
                cout << "Password (Minimal 8 angka): "; cin >> pass;
                if (loginUser(dataUser, uName, pass, "pembeli")) {
                    menuPembeli(daftarBarang, uName);
                } else {
                    cout << ">> Gagal! Akun tidak ditemukan atau salah password.\n";
                }
            }
        
        } else if (pilAwal == 2) { // --- MENU REGISTER ---
            cout << "\n--- REGISTER AKUN BARU ---\n";
            cout << "1. Daftar jadi Penjual\n";
            cout << "2. Daftar jadi Pembeli\n";
            cout << "Pilih: "; cin >> pilLogin;
            
            cout << "Buat Username: "; cin >> uName;
            cout << "Buat Password (Minimal 8 angka): "; cin >> pass;

            if (pilLogin == 1) registerUser(dataUser, uName, pass, "penjual");
            else if (pilLogin == 2) registerUser(dataUser, uName, pass, "pembeli");
        }
        
        cout << "\nTekan Enter...";
        cin.ignore(); cin.get();
    }

    return 0;
}