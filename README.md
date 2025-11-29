# 🏛️ Online Auction System (Sistem Pelelangan Online)

![Language](https://img.shields.io/badge/Language-C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B)
![Course](https://img.shields.io/badge/Course-Struktur_Data-orange?style=for-the-badge)
![Status](https://img.shields.io/badge/Status-On_Progress-green?style=for-the-badge)

> **Tugas Besar (Tubes) Mata Kuliah Struktur Data** > Program aplikasi berbasis CLI (Command Line Interface) untuk mensimulasikan proses lelang barang secara *real-time* dan terstruktur.

---

## 👥 Anggota Kelompok 2

| No | Nama Mahasiswa | Peran (Role) | GitHub |
| :---: | :--- | :--- | :---: |
| 1. | **Muhammad Zaky Mubarok** | *Backend & Logic* | [@Zackjek](https://github.com/Zackjek) |
| 2. | **Ichya Ulumiddin** | *Data Structure Implementation* | - |
| 3. | **Aril Ahnaf Kusuma** | *Frontend CLI & Flow* | - |


---

## 📚 Deskripsi Proyek

Aplikasi ini dirancang untuk mempertemukan penjual dan pembeli dalam sistem lelang terbuka. Pengguna dapat mendaftarkan barang, melakukan penawaran (bid), dan menentukan pemenang lelang berdasarkan harga tertinggi.

**Fitur Utama:**
* ✅ **Manajemen User:** Pendaftaran pelelang dan penawar.
* ✅ **Listing Barang:** Menambahkan barang yang akan dilelang.
* ✅ **Sistem Bidding:** Mekanisme tawar-menawar harga.
* ✅ **Riwayat Transaksi:** Mencatat sejarah pemenang lelang.

---

## 🛠️ Struktur Data yang Digunakan

Proyek ini mengimplementasikan konsep Struktur Data berikut untuk efisiensi memori dan kecepatan:

* **Single Linked List:** Untuk menyimpan daftar barang yang sedang dilelang.
* **Queue (Antrean):** Untuk mengatur urutan penawaran (bid) yang masuk.
* **Stack (Tumpukan):** Untuk fitur *undo* atau riwayat navigasi menu.
* **Searching & Sorting:** Algoritma untuk mencari barang dan mengurutkan harga tertinggi.

---

## 💻 Cara Menjalankan Program

Pastikan compiler C++ (MinGW/G++) sudah terinstall.

1.  **Clone Repository**
    ```bash
    git clone [https://github.com/Zackjek/Tubes-Strukdat.git](https://github.com/Zackjek/Tubes-Strukdat.git)
    ```
2.  **Masuk ke Direktori**
    ```bash
    cd Tubes-Strukdat
    ```
3.  **Compile Program**
    ```bash
    g++ main.cpp tubes.cpp -o main
    ```
4.  **Jalankan**
    ```bash
    ./main
    ```

---

## 📸 Dokumentasi / Screenshot

*(Coming Soon - Akan ditambahkan setelah program selesai)*

---

<p align="center">
  Dibuat dengan ❤️ dan ☕ oleh Mahasiswa Telkom University Purwokerto
</p>