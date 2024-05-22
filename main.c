#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROOMS 100
#define MAX_CUSTOMERS 100
#define MAX_NAME_LEN 50
#define PRICE_PER_NIGHT 100 // Harga per malam dalam satuan mata uang yang relevan

typedef struct {
    int roomNumber;
    int isAvailable;
} Room;

typedef struct {
    char name[MAX_NAME_LEN];
    char email[MAX_NAME_LEN];
    int roomNumber;
    int nights;
    int numberOfGuests;
    float totalBill;
} Customer;

Room rooms[MAX_ROOMS];
Customer customers[MAX_CUSTOMERS];
int currentCustomers = 0;

void initializeRooms() {
    for (int i = 0; i < MAX_ROOMS; i++) {
        rooms[i].roomNumber = i + 1;
        rooms[i].isAvailable = 1; // Semua kamar tersedia awalnya
    }
}

void addCustomer(char *name, char *email, int roomNumber, int nights, int numberOfGuests) {
    if (currentCustomers >= MAX_CUSTOMERS) {
        printf("Batas pelanggan tercapai!\n");
        return;
    }
    if (roomNumber <= 0 || roomNumber > MAX_ROOMS || !rooms[roomNumber - 1].isAvailable) {
        printf("Nomor kamar tidak valid atau kamar tidak tersedia!\n");
        return;
    }
    if (numberOfGuests > 2) {
        printf("Jumlah tamu per kamar tidak boleh lebih dari 2!\n");
        return;
    }
    rooms[roomNumber - 1].isAvailable = 0;
    strcpy(customers[currentCustomers].name, name);
    strcpy(customers[currentCustomers].email, email);
    customers[currentCustomers].roomNumber = roomNumber;
    customers[currentCustomers].nights = nights;
    customers[currentCustomers].numberOfGuests = numberOfGuests;
    customers[currentCustomers].totalBill = nights * PRICE_PER_NIGHT;
    currentCustomers++;
    printf("Pelanggan berhasil ditambahkan!\n");
}

void checkOutCustomer(int roomNumber) {
    for (int i = 0; i < currentCustomers; i++) {
        if (customers[i].roomNumber == roomNumber) {
            printf("Total tagihan untuk kamar %d: %.2f\n", roomNumber, customers[i].totalBill);
            rooms[roomNumber - 1].isAvailable = 1;
            for (int j = i; j < currentCustomers - 1; j++) {
                customers[j] = customers[j + 1];
            }
            currentCustomers--;
            printf("Pelanggan berhasil check-out!\n");
            return;
        }
    }
    printf("Tidak ada pelanggan di kamar %d\n", roomNumber);
}

void listAvailableRooms() {
    printf("Kamar yang tersedia:\n");
    for (int i = 0; i < MAX_ROOMS; i++) {
        if (rooms[i].isAvailable) {
            printf("Kamar %d\n", rooms[i].roomNumber);
        }
    }
}

void listCustomers() {
    printf("Pelanggan saat ini:\n");
    for (int i = 0; i < currentCustomers; i++) {
        printf("Nama: %s, Email: %s, Kamar: %d, Malam: %d, Jumlah Tamu: %d, Tagihan: %.2f\n",
               customers[i].name, customers[i].email, customers[i].roomNumber,
               customers[i].nights, customers[i].numberOfGuests, customers[i].totalBill);
    }
}

void helpMenu() {
    printf("Menu Bantuan - Fitur Program:\n");
    printf("1. Tambah Pelanggan - Menambahkan pelanggan baru ke dalam sistem.\n");
    printf("2. Check-Out Pelanggan - Mengeluarkan pelanggan dan menyelesaikan tagihan.\n");
    printf("3. Daftar Kamar Tersedia - Menampilkan semua kamar yang tersedia.\n");
    printf("4. Daftar Pelanggan Saat Ini - Menampilkan daftar semua pelanggan yang sedang menginap.\n");
    printf("5. Bantuan - Menampilkan menu bantuan ini.\n");
    printf("6. Keluar - Keluar dari program.\n");
}

int main() {
    initializeRooms();
    int choice, roomNumber, nights, numberOfGuests;
    char name[MAX_NAME_LEN], email[MAX_NAME_LEN];

    while (1) {
        printf("\nSistem Manajemen Hotel\n");
        printf("1. Tambah Pelanggan\n");
        printf("2. Check-Out Pelanggan\n");
        printf("3. Daftar Kamar Tersedia\n");
        printf("4. Daftar Pelanggan Saat Ini\n");
        printf("5. Bantuan\n");
        printf("6. Keluar\n");
        printf("Masukkan pilihan Anda: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Masukkan nama pelanggan: ");
                scanf("%s", name);
                printf("Masukkan email pelanggan: ");
                scanf("%s", email);
                printf("Masukkan nomor kamar: ");
                scanf("%d", &roomNumber);
                printf("Masukkan jumlah malam menginap: ");
                scanf("%d", &nights);
                printf("Masukkan jumlah tamu (maks 2): ");
                scanf("%d", &numberOfGuests);
                addCustomer(name, email, roomNumber, nights, numberOfGuests);
                break;
            case 2:
                printf("Masukkan nomor kamar: ");
                scanf("%d", &roomNumber);
                checkOutCustomer(roomNumber);
                break;
            case 3:
                listAvailableRooms();
                break;
            case 4:
                listCustomers();
                break;
            case 5:
                helpMenu();
                break;
            case 6:
                exit(0);
            default:
                printf("Pilihan tidak valid!\n");
        }
    }

    return 0;
}