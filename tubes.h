#ifndef TUBES_H
#define TUBES_H

#include <iostream>
#include <string>
#include <fstream> // Tambahan untuk Save File

using namespace std;

// ==========================================
// 1. DEFINISI STRUKTUR DATA (ADT)
// ==========================================

// --- ADT STACK (Untuk Riwayat Bid) ---
struct BidInfo {
    string namaPenawar;
    double nominal;
};

typedef struct ElmStack *addressStack;
struct ElmStack {
    BidInfo info;
    addressStack next;
};
struct Stack {
    addressStack top;
};

// --- ADT CHILD MLL (Spesifikasi Barang) ---
// Anggota 2: Ini struktur Child untuk MLL
struct SpecInfo {
    string key;   // Contoh: "Warna"
    string value; // Contoh: "Merah"
};

typedef struct ElmSpec *addressSpec;
struct ElmSpec {
    SpecInfo info;
    addressSpec next;
};

// --- ADT LIST PARENT (Daftar Barang) ---
// Anggota 2: Ini struktur Parent
struct ItemInfo {
    int id;
    string namaBarang;
    string penjual;
    double hargaAwal;
    string status;      // "PENDING", "AKTIF"
    Stack historyBid;   // Stack bid per barang
    addressSpec firstSpec; // Pointer ke Child (Spesifikasi)
};

typedef struct ElmList *addressList;
struct ElmList {
    ItemInfo info;
    addressList next;
};
struct List {
    addressList first;
};

// --- ADT TREE (Untuk Pencarian BST) ---
// Anggota 1: Struktur Tree untuk sorting/searching
typedef struct TreeNode *addressTree;
struct TreeNode {
    string namaBarang;      // Key untuk sorting
    addressList originalItem; // Pointer ke data asli di List
    addressTree left;
    addressTree right;
};

// ==========================================
// 2. PROTOTYPE FUNGSI (Header)
// ==========================================

// Primitif Stack (Anggota 1)
void createStack(Stack &S);
void push(Stack &S, string nama, double harga);
void printStack(Stack S);
double getMaxBid(Stack S);

// Primitif List & MLL (Anggota 2 - TUGAS KAMU)
void createList(List &L);
void insertLast(List &L, string nama, double harga, string penjual, int &autoID);
void addSpec(addressList P, string key, string value); // Tambah spek ke barang P
addressList searchByID(List L, int id);
void printList(List L); // Saya update biar simpel dulu tanpa parameter role
void saveToFile(List L); // Fitur tambahan kamu

// Primitif Tree (Anggota 1)
addressTree insertTree(addressTree root, addressList itemPtr);
addressList searchTree(addressTree root, string namaDicari);

// Menu & Utils (Anggota 3)
void menuAdmin(List &L);
void menuPenjual(List &L, string username, int &counterID);
void menuPembeli(List &L, string username);
void menuCariBarang(List L);

#endif