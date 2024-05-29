#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mendefinisikan konstanta dan tipe data
#define MAKS_KAMAR 100
#define MAKS_TAMU 100
#define MAKS_PANJANG_NAMA 50
#define HARGA_DELUXE 1000000
#define HARGA_EXECUTIVE 3000000
#define HARGA_PRESIDENTIAL 20000000

// Mendefinisikan tipe enum untuk jenis kamar
typedef enum {
    DELUXE,
    EXECUTIVE,
    PRESIDENTIAL
} TipeKamar;

// Struct untuk menyimpan informasi kamar
typedef struct {
    int nomorKamar;
    TipeKamar tipe;
    int tersedia;
} Kamar;

// Struct untuk menyimpan informasi tamu
typedef struct {
    char nama[MAKS_PANJANG_NAMA];
    char email[MAKS_PANJANG_NAMA];
    int nomorKamar;
    int malam;
    int jumlahTamu;
    int totalTagihan;
    TipeKamar tipeKamar;
} Tamu;

// Mendeklarasi array untuk menyimpan data kamar dan tamu
Kamar kamar[MAKS_KAMAR];
Tamu tamu[MAKS_TAMU];
int jumlahTamuSaatIni = 0;

// Inisialisasi kamar
void inisialisasiKamar() {
    int i;
    // Inisialisasi kamar deluxe
    for (i = 0; i < 70; i++) {
        kamar[i].nomorKamar = i + 1;
        kamar[i].tipe = DELUXE;
        kamar[i].tersedia = 1;
    }
    // Inisialisasi kamar executive
    for (; i < 95; i++) {
        kamar[i].nomorKamar = i + 1;
        kamar[i].tipe = EXECUTIVE;
        kamar[i].tersedia = 1;
    }
    // Inisialisasi kamar presidential
    for (; i < MAKS_KAMAR; i++) {
        kamar[i].nomorKamar = i + 1;
        kamar[i].tipe = PRESIDENTIAL;
        kamar[i].tersedia = 1;
    }
}

// Fungsi untuk mendapatkan harga kamar berdasarkan tipe
int dapatkanHargaKamar(TipeKamar tipe) {
    switch (tipe) {
        case DELUXE: return HARGA_DELUXE;
        case EXECUTIVE: return HARGA_EXECUTIVE;
        case PRESIDENTIAL: return HARGA_PRESIDENTIAL;
        default: return 0;
    }
}

// Fungsi untuk mendapatkan nama tipe kamar sebagai string
const char* dapatkanNamaTipeKamar(TipeKamar tipe) {
    switch (tipe) {
        case DELUXE: return "Deluxe";
        case EXECUTIVE: return "Executive";
        case PRESIDENTIAL: return "Presidential";
        default: return "Tidak Diketahui";
    }
}

// Fungsi untuk menampilkan kamar yang tersedia berdasarkan tipe
void daftarKamarTersediaBerdasarkanTipe(TipeKamar tipe) {
    printf("Kamar yang tersedia (%s):\n", dapatkanNamaTipeKamar(tipe));
    for (int i = 0; i < MAKS_KAMAR; i++) {
        if (kamar[i].tersedia && kamar[i].tipe == tipe) {
            printf("Kamar %d\n", kamar[i].nomorKamar);
        }
    }
}

// Fungsi untuk menambahkan tamu baru
void tambahkanTamu(char *nama, char *email, int nomorKamar, int malam, int jumlahTamu) {
    // Periksa apakah jumlah tamu sudah mencapai batas
    if (jumlahTamuSaatIni >= MAKS_TAMU) {
        printf("Batas tamu tercapai!\n");
        return;
    }
    // Periksa validitas nomor kamar dan ketersediaannya
    if (nomorKamar <= 0 || nomorKamar > MAKS_KAMAR || !kamar[nomorKamar - 1].tersedia) {
        printf("Nomor kamar tidak valid atau kamar tidak tersedia!\n");
        return;
    }
    // Periksa jumlah tamu
    if (jumlahTamu > 2) {
        printf("Jumlah tamu per kamar tidak boleh lebih dari 2!\n");
        return;
    }
    // Tandai kamar sebagai tidak tersedia
    kamar[nomorKamar - 1].tersedia = 0;
    TipeKamar tipeKamar = kamar[nomorKamar - 1].tipe;
    // Salin informasi tamu ke Struct tamu
    strncpy(tamu[jumlahTamuSaatIni].nama, nama, MAKS_PANJANG_NAMA);
    strncpy(tamu[jumlahTamuSaatIni].email, email, MAKS_PANJANG_NAMA);
    tamu[jumlahTamuSaatIni].nomorKamar = nomorKamar;
    tamu[jumlahTamuSaatIni].malam = malam;
    tamu[jumlahTamuSaatIni].jumlahTamu = jumlahTamu;
    tamu[jumlahTamuSaatIni].tipeKamar = tipeKamar;
    tamu[jumlahTamuSaatIni].totalTagihan = malam * dapatkanHargaKamar(tipeKamar);
    // Tambahkan tamu ke dalam daftar tamu
    jumlahTamuSaatIni++;
    printf("Tamu berhasil ditambahkan!\n");
}

// Fungsi untuk check-out tamu
void checkOutTamu(int nomorKamar) {
    for (int i = 0; i < jumlahTamuSaatIni; i++) {
        if (tamu[i].nomorKamar == nomorKamar) {
            // Tampilkan informasi tamu untuk konfirmasi
            printf("Informasi Tamu:\n");
            printf("Nama: %s\n", tamu[i].nama);
            printf("Jumlah Malam: %d\n", tamu[i].malam);
            printf("Tagihan: %d juta rupiah\n", tamu[i].totalTagihan / 1000000);

            // Minta konfirmasi dari pengguna
            char konfirmasi;
            printf("Apakah Anda yakin ingin melanjutkan check-out? (y/n): ");
            scanf(" %c", &konfirmasi); // Catatan: ruang sebelum %c untuk melewati spasi yang ada
            if (konfirmasi == 'y' || konfirmasi == 'Y') {
                printf("Melanjutkan proses check-out...\n");
                kamar[nomorKamar - 1].tersedia = 1;
                // Hapus tamu dari daftar
                for (int j = i; j < jumlahTamuSaatIni - 1; j++) {
                    tamu[j] = tamu[j + 1];
                }
                jumlahTamuSaatIni--;
                printf("Tamu berhasil check-out!\n");
            } else {
                printf("Check-out dibatalkan.\n");
            }
            return;
        }
    }
    printf("Tidak ada tamu di kamar %d\n", nomorKamar);
}

// Fungsi untuk menampilkan daftar kamar yang tersedia
void daftarKamarTersedia() {
    printf("Kamar yang tersedia:\n");
    for (int i = 0; i < MAKS_KAMAR; i++) {
        if (kamar[i].tersedia) {
            printf("Kamar %d (%s)\n", kamar[i].nomorKamar, 
                   kamar[i].tipe == DELUXE ? "Deluxe" :
                   kamar[i].tipe == EXECUTIVE ? "Executive" : "Presidential");
        }
    }
}

// Fungsi untuk menampilkan daftar tamu saat ini
void daftarTamuSaatIni() {
    printf("Tamu saat ini:\n");
    for (int i = 0; i < jumlahTamuSaatIni; i++) {
        printf("Nama: %s, Email: %s, Kamar: %d (%s), Malam: %d, Jumlah Tamu: %d, Tagihan: %d juta rupiah\n",
               tamu[i].nama, tamu[i].email, tamu[i].nomorKamar,
               dapatkanNamaTipeKamar(tamu[i].tipeKamar),
               tamu[i].malam, tamu[i].jumlahTamu, tamu[i].totalTagihan / 1000000);
    }
}

// Fungsi untuk menampilkan menu bantuan
void menuBantuan() {
    printf("Menu Bantuan - Fitur Program:\n");
    printf("1. Tambah Tamu - Menambahkan tamu baru ke dalam sistem.\n");
    printf("2. Check-Out Tamu - Mengeluarkan tamu dan menyelesaikan tagihan.\n");
    printf("3. Daftar Kamar Tersedia - Menampilkan semua kamar yang tersedia.\n");
    printf("4. Daftar Tamu Saat Ini - Menampilkan daftar semua tamu yang sedang menginap.\n");
    printf("5. Bantuan - Menampilkan menu bantuan ini.\n");
    printf("6. Keluar - Keluar dari program.\n");
}

// Fungsi untuk memilih tipe kamar
int pilihTipeKamar() {
    int tipeKamar;
    printf("Pilih tipe kamar:\n");
    printf("1. Deluxe\n");
    printf("2. Executive\n");
    printf("3. Presidential\n");
    printf("Masukkan pilihan Anda: ");
    scanf("%d", &tipeKamar);
    return tipeKamar - 1; // Mengurangi 1 untuk menyesuaikan dengan enum TipeKamar
}

// Fungsi untuk memilih nomor kamar
int pilihNomorKamar(TipeKamar tipeKamar) {
    int nomorKamar;
    daftarKamarTersediaBerdasarkanTipe(tipeKamar);
    printf("Masukkan nomor kamar yang dipilih: ");
    scanf("%d", &nomorKamar);
    return nomorKamar;
}

// Fungsi utama
int main() {
    inisialisasiKamar();
    int pilihan, nomorKamar, malam, jumlahTamu;
    char nama[MAKS_PANJANG_NAMA], email[MAKS_PANJANG_NAMA];

    while (1) {
        // Tampilkan menu utama
        printf("\nSistem Manajemen Hotel\n");
        printf("1. Tambah Tamu\n");
        printf("2. Check-Out Tamu\n");
        printf("3. Daftar Kamar Tersedia\n");
        printf("4. Daftar Tamu Saat Ini\n");
        printf("5. Bantuan\n");
        printf("6. Keluar\n");
        printf("Masukkan pilihan Anda: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                // Tambah tamu
                printf("Masukkan jumlah tamu (maks 2): ");
                scanf("%d", &jumlahTamu);
                if (jumlahTamu > 2) {
                    printf("Jumlah tamu per kamar tidak boleh lebih dari 2!\n");
                    break;
                }
                getchar(); // Bersihkan karakter newline dari buffer
                printf("Masukkan nama tamu: ");
                fgets(nama, MAKS_PANJANG_NAMA, stdin);
                nama[strcspn(nama, "\n")] = 0; // Hapus karakter newline jika ada
                printf("Masukkan email tamu: ");
                fgets(email, MAKS_PANJANG_NAMA, stdin);
                email[strcspn(email, "\n")] = 0; // Hapus karakter newline jika ada
                int tipeKamar = pilihTipeKamar();
                if (tipeKamar < 0 || tipeKamar > 2) {
                    printf("Pilihan tipe kamar tidak valid!\n");
                    break;
                }
                nomorKamar = pilihNomorKamar((TipeKamar)tipeKamar);
                printf("Masukkan jumlah malam menginap: ");
                scanf("%d", &malam);
                tambahkanTamu(nama, email, nomorKamar, malam, jumlahTamu);
                break;
            case 2:
                // Check-out tamu
                printf("Masukkan nomor kamar: ");
                scanf("%d", &nomorKamar);
                checkOutTamu(nomorKamar);
                break;
            case 3:
                // Daftar kamar yang tersedia
                daftarKamarTersedia();
                break;
            case 4:
                // Daftar tamu saat ini
                daftarTamuSaatIni();
                break;
            case 5:
                // Menu bantuan
                menuBantuan();
                break;
            case 6:
                // Keluar dari program
                exit(0);
            default:
                // Pilihan tidak valid
                printf("Pilihan tidak valid!\n");
        }
    }

    return 0;
}

