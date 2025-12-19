#include "tubes.h"
#include <fstream>
#include <iomanip>

// ==========================================
//      BAGIAN 1: PRIMITIF STACK (History Bid)
//      (Tugas Anggota 1 - Saya rapikan biar jalan)
// ==========================================

void createStack(Stack &S) {
    S.top = NULL;
}

void push(Stack &S, string nama, double harga) {
    addressStack P = new ElmStack;
    P->info.namaPenawar = nama;
    P->info.nominal = harga;
    P->next = S.top;
    S.top = P;
}

void printStack(Stack S) {
    if (S.top == NULL) {
        cout << "      (Belum ada penawaran)" << endl;
    } else {
        addressStack P = S.top;
        while (P != NULL) {
            cout << "      > " << P->info.namaPenawar << ": Rp" << (long)P->info.nominal << endl;
            P = P->next;
        }
    }
}

double getMaxBid(Stack S) {
    if (S.top == NULL) return 0;
    return S.top->info.nominal;
}

// ==========================================
//      BAGIAN 2: PRIMITIF MLL (List & Spesifikasi)
//      (TUGAS KAMU - ANGGOTA 2)
// ==========================================

void createList(List &L) {
    L.first = NULL;
}

// Insert Barang (Parent)
void insertLast(List &L, string nama, double harga, string penjual, int &autoID) {
    addressList P = new ElmList;
    P->info.id = autoID;
    P->info.namaBarang = nama;
    P->info.hargaAwal = harga;
    P->info.penjual = penjual;
    P->info.status = "PENDING"; 
    P->info.firstSpec = NULL;
    
    // Inisialisasi Stack History Bid
    createStack(P->info.historyBid);

    P->next = NULL;
    autoID++; 

    if (L.first == NULL) {
        L.first = P;
    } else {
        addressList Q = L.first;
        while (Q->next != NULL) {
            Q = Q->next;
        }
        Q->next = P;
    }
}

// Tambah Spesifikasi (Child)
void addSpec(addressList P, string key, string value) {
    if (P == NULL) return;

    addressSpec newSpec = new ElmSpec;
    newSpec->info.key = key;
    newSpec->info.value = value;
    newSpec->next = NULL;

    if (P->info.firstSpec == NULL) {
        P->info.firstSpec = newSpec;
    } else {
        addressSpec Q = P->info.firstSpec;
        while (Q->next != NULL) {
            Q = Q->next;
        }
        Q->next = newSpec;
    }
}

// Cari Barang by ID (Bantuan untuk insert spek)
addressList searchByID(List L, int id) {
    addressList P = L.first;
    while (P != NULL) {
        if (P->info.id == id) {
            return P;
        }
        P = P->next;
    }
    return NULL;
}

// Print List Lengkap (Parent + Child + History Bid)
void printList(List L) { // Hapus parameter role/username biar simpel
    if (L.first == NULL) {
        cout << "   [Belum ada barang terdaftar]\n";
        return;
    }

    addressList P = L.first;
    while (P != NULL) {
        cout << "------------------------------------------------\n";
        cout << "ID: " << P->info.id << " | " << P->info.namaBarang 
             << " | Rp" << (long)P->info.hargaAwal << endl;
        cout << "Penjual: " << P->info.penjual << " | Status: " << P->info.status << endl;
        
        // Tampilkan Spek
        addressSpec Q = P->info.firstSpec;
        if (Q == NULL) cout << "   (No Specs)\n";
        else {
            cout << "   Spesifikasi:\n";
            while (Q != NULL) {
                cout << "   - " << Q->info.key << ": " << Q->info.value << endl;
                Q = Q->next;
            }
        }

        // Tampilkan History Bid (Intip Stack)
        cout << "   Riwayat Bid:\n";
        printStack(P->info.historyBid);
        
        cout << "------------------------------------------------\n";
        P = P->next;
    }
}

void saveToFile(List L) {
    ofstream file("data_lelang.txt");
    addressList P = L.first;
    while (P != NULL) {
        file << "BARANG|" << P->info.id << "|" << P->info.namaBarang 
             << "|" << (long)P->info.hargaAwal << "|" << P->info.penjual << endl;
        
        addressSpec Q = P->info.firstSpec;
        while (Q != NULL) {
            file << "SPEK|" << Q->info.key << "|" << Q->info.value << endl;
            Q = Q->next;
        }
        P = P->next;
    }
    file.close();
    cout << ">> Data berhasil disimpan!\n";
}

// ==========================================
//      BAGIAN 3: PRIMITIF TREE (Searching)
//      (Tugas Anggota 1 - Placeholder Standard)
// ==========================================

addressTree insertTree(addressTree root, addressList itemPtr) {
    if (root == NULL) {
        root = new TreeNode;
        root->namaBarang = itemPtr->info.namaBarang;
        root->originalItem = itemPtr;
        root->left = NULL;
        root->right = NULL;
    } else {
        if (itemPtr->info.namaBarang < root->namaBarang) {
            root->left = insertTree(root->left, itemPtr);
        } else {
            root->right = insertTree(root->right, itemPtr);
        }
    }
    return root;
}

addressList searchTree(addressTree root, string namaDicari) {
    if (root == NULL) return NULL;
    if (root->namaBarang == namaDicari) return root->originalItem;
    
    if (namaDicari < root->namaBarang) 
        return searchTree(root->left, namaDicari);
    else 
        return searchTree(root->right, namaDicari);
}

// ==========================================
//      BAGIAN 4: MENU & INTERFACE
// ==========================================

void menuPenjual(List &L, string username, int &counterID) {
    int pil;
    do {
        cout << "\n--- DASHBOARD PENJUAL: " << username << " ---\n";
        cout << "1. Tambah Barang (Parent)\n";
        cout << "2. Tambah Spesifikasi (Child)\n";
        cout << "3. Lihat Barang Saya\n";
        cout << "4. Simpan Data\n";
        cout << "0. Kembali\n";
        cout << ">> "; cin >> pil;

        if (pil == 1) {
            string nama;
            double harga;
            cout << "Nama Barang: "; cin.ignore(); getline(cin, nama);
            cout << "Harga Awal : "; cin >> harga;
            insertLast(L, nama, harga, username, counterID);
            cout << "[Success] Barang ID " << counterID-1 << " dibuat.\n";
        } 
        else if (pil == 2) {
            printList(L);
            int id;
            cout << "Masukan ID Barang: "; cin >> id;
            addressList P = searchByID(L, id);
            if (P != NULL && P->info.penjual == username) {
                string k, v;
                cout << "Key (ex: RAM): "; cin >> k;
                cout << "Value (ex: 8GB): "; cin.ignore(); getline(cin, v);
                addSpec(P, k, v);
            } else {
                cout << "[Error] Barang tidak ditemukan atau bukan milikmu.\n";
            }
        }
        else if (pil == 3) {
            printList(L);
        }
        else if (pil == 4) {
            saveToFile(L);
        }
    } while (pil != 0);
}

void menuAdmin(List &L) {
    cout << "Fitur Admin (Validasi Barang) belum diimplementasi.\n";
}

void menuPembeli(List &L, string username) {
    int pil;
    do {
        cout << "\n--- MENU PEMBELI: " << username << " ---\n";
        cout << "1. Lihat Semua Barang\n";
        cout << "2. Bid Barang (Fitur Stack)\n";
        cout << "0. Kembali\n";
        cout << ">> "; cin >> pil;

        if (pil == 1) printList(L);
        else if (pil == 2) {
            int id;
            double tawaran;
            cout << "Masukkan ID Barang: "; cin >> id;
            addressList P = searchByID(L, id);
            if (P != NULL) {
                cout << "Harga saat ini: " << P->info.hargaAwal << endl;
                cout << "Bid tertinggi: " << getMaxBid(P->info.historyBid) << endl;
                cout << "Tawaranmu: "; cin >> tawaran;
                
                // Validasi sederhana
                if (tawaran > P->info.hargaAwal && tawaran > getMaxBid(P->info.historyBid)) {
                    push(P->info.historyBid, username, tawaran);
                    cout << "Bid Berhasil!\n";
                } else {
                    cout << "Bid terlalu rendah!\n";
                }
            }
        }
    } while (pil != 0);
}

void menuCariBarang(List L) {
    // Bangun Tree dulu dari List yang ada
    addressTree root = NULL;
    addressList P = L.first;
    while (P != NULL) {
        root = insertTree(root, P);
        P = P->next;
    }

    string cari;
    cout << "Masukkan Nama Barang persis (Case Sensitive): "; 
    cin.ignore(); getline(cin, cari);

    addressList hasil = searchTree(root, cari);
    if (hasil != NULL) {
        cout << "\n--- DITEMUKAN ---\n";
        cout << "ID: " << hasil->info.id << " | " << hasil->info.namaBarang << endl;
        cout << "Penjual: " << hasil->info.penjual << endl;
    } else {
        cout << "\n[Not Found] Barang tidak ditemukan di Tree.\n";
    }
}