# 🏛️ Sistem Lelang Online (Console App)

> **Status Proyek:** ✅ Final Release (Completed)
> **Bahasa:** C++ (Standard Library)
> **Basis Data:** File Handling (`.txt`)
> **Core Concept:** Multi Linked List, BST, & Stack

## 👨‍💻 Tim Pengembang (Developer Team)
> Disusun untuk memenuhi Tugas Besar Mata Kuliah Struktur Data

| No. | Nama Mahasiswa | NIM | Peran Utama (Role) | GitHub |
| :-: | :--- | :---: | :--- | :---: |
| 1. | Muhammad Zaky Mubarok | 103112400073 | [Zaky](https://github.com/Zackjek) |
| 2. | Ichya Ulumiddin | 103112400076 |  [Ichya](https://github.com/Ichya20) |
| 3. | Ariel Akhnaf Kusuma | 103112400050  | [Aril](https://github.com/wasdlover) |

---

## 📝 Gambaran Umum (Overview)
**Sistem Lelang Online** adalah aplikasi berbasis konsol (CLI) yang mensimulasikan proses pelelangan barang secara *real-time* dalam lingkup digital. Aplikasi ini menghubungkan tiga entitas utama: **Penjual**, **Pembeli**, dan **Admin** dalam satu ekosistem data yang terintegrasi.

Berbeda dengan aplikasi CRUD biasa, proyek ini menitikberatkan pada **efisiensi manajemen memori** dan **kompleksitas relasi data** menggunakan C++ murni (tanpa library database eksternal seperti SQL), melainkan membangun struktur data manual dari nol.

## 🌟 Fitur Unggulan
Sistem ini membagi fungsionalitas berdasarkan hak akses pengguna:

### 🛍️ Ekosistem Transaksi (User)
* **Secure Authentication:** Sistem Login & Register dengan validasi keamanan password (min. 8 karakter & alphanum).
* **Dynamic Inventory:** Penjual dapat menambahkan barang dan spesifikasinya secara dinamis (One-to-Many).
* **Smart Search Engine:** Pembeli dapat mencari barang dengan kata kunci tertentu menggunakan algoritma pencarian cepat.
* **Competitive Bidding:** Mekanisme tawar-menawar menggunakan sistem tumpukan harga (siapa cepat & tinggi, dia di atas).

### 🛠️ Panel Kontrol (Admin)
* **Moderasi Konten:** Validasi barang masuk (Approval System) sebelum tayang ke publik.
* **Penutupan Lelang:** Algoritma otomatis untuk menentukan pemenang lelang berdasarkan posisi teratas data tawaran.
* **Data Persistence:** Penyimpanan data otomatis ke file lokal sehingga data tidak hilang saat program ditutup.

---

## 🧠 Arsitektur Struktur Data
Proyek ini mengimplementasikan kombinasi 4 struktur data linear dan non-linear:

### 1. Multi Linked List (MLL) - Variasi Parent & Child
Digunakan sebagai tulang punggung penyimpanan data barang.
* **Parent Node (Barang):** Menyimpan ID, Nama, Harga Awal, dan Penjual.
* **Child Node (Spesifikasi):** Menyimpan detail atribut (contoh: RAM, Warna, Tahun).
* **Kenapa MLL?** Memungkinkan satu barang memiliki jumlah spesifikasi yang berbeda-beda tanpa memboroskan memori (fleksibel).

### 2. Binary Search Tree (BST)
Digunakan khusus untuk fitur **Pencarian (Searching)**.
* Setiap barang yang berstatus *AKTIF* akan di-*index* ke dalam Tree berdasarkan nama.
* **Keunggulan:** Mempercepat proses pencarian barang dari kompleksitas Linear O(n) menjadi Logaritmik O(log n).

### 3. Stack (LIFO)
Digunakan untuk menampung **Riwayat Penawaran (History Bid)** pada setiap barang.
* Tawaran terbaru/tertinggi selalu berada di elemen paling atas (*Top*).
* Memudahkan admin mengambil pemenang lelang (cukup ambil data *Top* tanpa harus sorting ulang).

### 4. File Handling (Custom Parsing)
Menggantikan database konvensional.
* Data disimpan dalam format teks mentah (`.txt`) dengan pemisah khusus (`|`).
* Saat program berjalan, sistem melakukan *parsing* untuk merekonstruksi ulang struktur MLL dari file teks.

---

## 📂 Struktur Direktori
```text
.
├── main.cpp           # Entry Point: Menu navigasi utama & Loop program
├── tubes.h            # Header: Definisi ADT (Struct) & Prototype fungsi
├── tubes.cpp          # Source: Implementasi logika algoritma (Insert, Delete, Search)
├── data_lelang.txt    # Database: Menyimpan data MLL Barang & Stack Bidding
└── data_users.txt     # Database: Menyimpan kredensial User & Role
