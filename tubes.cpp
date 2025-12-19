#include "tubes.h"
#include <fstream>
#include <sstream>

// --- FUNGSI BANTUAN ---
void cetakSpasi(int total, int terpakai) {
    int sisa = total - terpakai;
    if (sisa < 1) sisa = 1;
    for (int i = 0; i < sisa; i++) cout << " ";
}

// ==========================================
// IMPLEMENTASI STACK (RIWAYAT BID)
// ==========================================
void createStack(Stack &S) { 
    S.top = NULL; 
}

double getMaxBid(Stack S) {
    if (S.top == NULL) return 0;
    return S.top->info.nominal;
}

void push(Stack &S, string nama, double harga) {
    double currentMax = getMaxBid(S);
    
    if (harga <= currentMax) {
        cout << ">> GAGAL: Tawaran harus lebih tinggi dari Rp " << (long)currentMax << "!\n";
        return;
    }

    addressStack P = new ElmStack;
    P->info.namaPenawar = nama;
    P->info.nominal = harga;
    P->next = S.top;
    S.top = P;

    cout << ">> SUKSES: Tawaran Rp " << (long)harga << " diterima!\n";
}

void printStack(Stack S) {
    if (S.top == NULL) {
        cout << "        (Belum ada penawaran)\n";
    } else {
        addressStack P = S.top;
        while (P != NULL) {
            cout << "        -> Rp " << (long)P->info.nominal 
                 << " [" << P->info.namaPenawar << "]\n";
            P = P->next;
        }
    }
}

// ==========================================
// IMPLEMENTASI MLL (BARANG + SPEC)
// ==========================================
void createList(List &L) { L.first = NULL; }

void insertLast(List &L, string nama, double harga, string penjual, int &autoID) {
    addressList P = new ElmList;
    P->info.id = ++autoID;
    P->info.namaBarang = nama;
    P->info.hargaAwal = harga;
    P->info.penjual = penjual;
    P->info.status = "PENDING";
    createStack(P->info.historyBid);
    P->info.firstSpec = NULL;
    P->next = NULL;

    if (L.first == NULL) L.first = P;
    else {
        addressList last = L.first;
        while (last->next != NULL) last = last->next;
        last->next = P;
    }
}

void addSpec(addressList P, string key, string value) {
    addressSpec S = new ElmSpec;
    S->info.key = key;
    S->info.value = value;
    S->next = NULL;

    if (P->info.firstSpec == NULL) {
        P->info.firstSpec = S;
    } else {
        addressSpec last = P->info.firstSpec;
        while (last->next != NULL) last = last->next;
        last->next = S;
    }
}

addressList searchByID(List L, int id) {
    addressList P = L.first;
    while (P != NULL) {
        if (P->info.id == id) return P;
        P = P->next;
    }
    return NULL;
}

void printList(List L, string role, string username) {
    addressList P = L.first;
    bool found = false;
    cout << "\nDAFTAR BARANG (MLL):\n";
    cout << "=================================================================\n";
    
    while (P != NULL) {
        bool show = false;
        if (role == "admin") show = true;
        else if (role == "penjual" && P->info.penjual == username) show = true;
        else if (role == "pembeli" && P->info.status == "AKTIF") show = true;

        if (show) {
            double currentPrice = P->info.hargaAwal;
            double topBid = getMaxBid(P->info.historyBid);
            if (topBid > currentPrice) currentPrice = topBid;

            cout << "ID: " << P->info.id << " | " << P->info.namaBarang;
            cout << " | Penjual: " << P->info.penjual << endl;
            cout << "   Harga: Rp " << (long)currentPrice << " (Awal: " << (long)P->info.hargaAwal << ")\n";
            cout << "   Status: " << P->info.status << endl;
            
            cout << "   [Spesifikasi]: ";
            addressSpec S = P->info.firstSpec;
            if (S == NULL) cout << "-";
            while (S != NULL) {
                cout << S->info.key << ":" << S->info.value;
                if (S->next != NULL) cout << ", ";
                S = S->next;
            }
            cout << endl;
            cout << "-----------------------------------------------------------------\n";
            found = true;
        }
        P = P->next;
    }
    if (!found) cout << "   (Tidak ada data yang sesuai)\n";
}

// ==========================================
// IMPLEMENTASI TREE (SEARCHING)
// ==========================================
addressTree insertTree(addressTree root, addressList itemPtr) {
    if (root == NULL) {
        addressTree P = new TreeNode;
        P->namaBarang = itemPtr->info.namaBarang;
        P->originalItem = itemPtr;
        P->left = NULL; 
        P->right = NULL;
        return P;
    }

    if (itemPtr->info.namaBarang < root->namaBarang) {
        root->left = insertTree(root->left, itemPtr);
    } else if (itemPtr->info.namaBarang > root->namaBarang) {
        root->right = insertTree(root->right, itemPtr);
    }
    return root;
}

addressList searchTree(addressTree root, string namaDicari) {
    if (root == NULL) return NULL;
    
    // Partial Match Logic
    if (root->namaBarang.find(namaDicari) != string::npos) {
        return root->originalItem;
    }
    
    addressList hasilKiri = searchTree(root->left, namaDicari);
    if (hasilKiri != NULL) return hasilKiri;
    
    return searchTree(root->right, namaDicari);
}

// ==========================================
// MENU UTAMA LOGIC
// ==========================================
void menuAdmin(List &L) {
    int pil;
    do {
        cout << "\n[MENU ADMIN]\n1. Lihat & Setujui Barang\n2. Lihat History Bid\n3. Simpan Data (File)\n0. Kembali\nPilih: "; 
        cin >> pil;
        if (pil == 1) {
            printList(L, "admin", "");
            cout << "Masukkan ID Barang utk disetujui (0 batal): ";
            int id; cin >> id;
            if (id!=0) {
                addressList item = searchByID(L, id);
                if(item) { item->info.status = "AKTIF"; cout << "Sukses!\n"; }
            }
        } else if (pil == 2) {
            printList(L, "admin", "");
            cout << "ID Barang: "; int id; cin >> id;
            addressList item = searchByID(L, id);
            if(item) { 
                cout << "History Bid " << item->info.namaBarang << ":\n";
                printStack(item->info.historyBid);
            }
        } else if (pil == 3) {
            saveToFile(L);
        }
    } while (pil != 0);
}

void menuPenjual(List &L, string username, int &counterID) {
    int pil;
    do {
        cout << "\n[MENU PENJUAL: " << username << "]\n1. Tambah Barang\n2. Lihat Barang Saya\n0. Kembali\nPilih: ";
        cin >> pil;
        if (pil == 1) {
            string nama; double harga;
            
            cout << "Nama Barang: ";
            cin.ignore();          
            getline(cin, nama);    
            
            cout << "Harga Awal : "; 
            cin >> harga;          
            
            insertLast(L, nama, harga, username, counterID);
            
            // Input Spesifikasi
            addressList P = searchByID(L, counterID);
            char tambahSpec;
            do {
                cout << "Tambah Spesifikasi? (y/n): "; cin >> tambahSpec;
                if (tambahSpec == 'y' || tambahSpec == 'Y') {
                    string k, v;
                    cout << "- Nama Spec (ex: Warna): "; cin >> k;
                    cout << "- Isi Spec  (ex: Merah): "; cin >> v;
                    addSpec(P, k, v);
                }
            } while (tambahSpec == 'y' || tambahSpec == 'Y');
            
            cout << "Barang & Spesifikasi tersimpan sementara!\n";
            saveToFile(L); // Auto-save tugas Anggota 2
            
        } else if (pil == 2) {
            printList(L, "penjual", username);
        }
    } while (pil != 0);
}

void menuPembeli(List &L, string username) {
    int pil;
    do {
        cout << "\n[MENU PEMBELI: " << username << "]\n1. Katalog & Bid\n0. Kembali\nPilih: ";
        cin >> pil;
        if (pil == 1) {
            printList(L, "pembeli", username);
            cout << "ID Barang utk Bid (0 batal): "; int id; cin >> id;
            if (id != 0) {
                addressList item = searchByID(L, id);
                if (item && item->info.status == "AKTIF") {
                    double maxBid = item->info.hargaAwal;
                    double topS = getMaxBid(item->info.historyBid);
                    if (topS > maxBid) maxBid = topS;
                    
                    cout << "Highest Bid: " << (long)maxBid << endl;
                    cout << "Tawaranmu  : "; double tawaran; cin >> tawaran;
                    
                    if (tawaran > maxBid) {
                        push(item->info.historyBid, username, tawaran);
                        cout << "Sukses!\n";
                    } else cout << "Gagal! Tawaran terlalu rendah.\n";
                } else cout << "Item tidak valid.\n";
            }
        }
    } while (pil != 0);
}

void menuCariBarang(List L) {
    if (L.first == NULL) {
        cout << ">> Belum ada barang untuk dicari.\n";
        return;
    }

    addressTree root = NULL;
    addressList P = L.first;
    while (P != NULL) {
        if (P->info.status == "AKTIF") {
            root = insertTree(root, P);
        }
        P = P->next;
    }

    if (root == NULL) {
        cout << ">> Tidak ada barang AKTIF yang bisa dicari.\n";
        return;
    }

    string cari;
    cout << "Masukkan Nama Barang: ";
    cin.ignore();          
    getline(cin, cari);    
    
    // Perbaikan Bug: Deklarasi variabel hanya sekali
    addressList hasil = searchTree(root, cari);

    if (hasil != NULL) {
        cout << "\n>> BARANG DITEMUKAN!\n";
        cout << "==========================\n";
        cout << "ID      : " << hasil->info.id << endl;
        cout << "Nama    : " << hasil->info.namaBarang << endl;
        cout << "Penjual : " << hasil->info.penjual << endl;
        cout << "Harga   : Rp " << (long)hasil->info.hargaAwal << endl;
        cout << "Bid Tertinggi Saat Ini: Rp " << (long)getMaxBid(hasil->info.historyBid) << endl;
        cout << "==========================\n";
        
        cout << "Ingin menawar barang ini? (y/n): ";
        char jawab; cin >> jawab;
        if (jawab == 'y' || jawab == 'Y') {
            string penawar; double nominal;
            cout << "Nama Anda: "; cin >> penawar;
            cout << "Nominal  : "; cin >> nominal;
            push(hasil->info.historyBid, penawar, nominal);
        }

    } else {
        cout << ">> Barang '" << cari << "' tidak ditemukan.\n";
    }
}

// ==========================================
// [TAMBAHAN ANGGOTA 2: FILE HANDLING]
// ==========================================
void saveToFile(List L) {
    ofstream file("data_lelang.txt");
    if (!file.is_open()) return;

    addressList P = L.first;
    while (P != NULL) {
        // BARANG|ID|Nama|Harga|Penjual|Status
        file << "BARANG|" << P->info.id << "|" << P->info.namaBarang << "|" 
             << (long)P->info.hargaAwal << "|" << P->info.penjual << "|" 
             << P->info.status << endl;
        
        // SPEK|ID_Barang|Key|Value
        addressSpec Q = P->info.firstSpec;
        while (Q != NULL) {
            file << "SPEK|" << P->info.id << "|" << Q->info.key << "|" << Q->info.value << endl;
            Q = Q->next;
        }
        P = P->next;
    }
    file.close();
    cout << "   (Data tersimpan ke file)\n";
}

void loadFromFile(List &L, int &lastID) {
    ifstream file("data_lelang.txt");
    if (!file.is_open()) return;

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string segment;
        string data[6];
        int i = 0;

        while(getline(ss, segment, '|') && i < 6) {
            data[i] = segment;
            i++;
        }

        if (data[0] == "BARANG") {
            int id = stoi(data[1]);
            string nama = data[2];
            double harga = stod(data[3]);
            string penjual = data[4];
            string status = data[5];

            addressList P = new ElmList;
            P->info.id = id;
            P->info.namaBarang = nama;
            P->info.hargaAwal = harga;
            P->info.penjual = penjual;
            P->info.status = status;
            createStack(P->info.historyBid);
            P->info.firstSpec = NULL;
            P->next = NULL;

            if (L.first == NULL) L.first = P;
            else {
                addressList last = L.first;
                while (last->next != NULL) last = last->next;
                last->next = P;
            }

            if (id > lastID) lastID = id;

        } else if (data[0] == "SPEK") {
            int idBarang = stoi(data[1]);
            string key = data[2];
            string val = data[3];

            addressList item = searchByID(L, idBarang);
            if (item != NULL) {
                addSpec(item, key, val);
            }
        }
    }
    file.close();
}