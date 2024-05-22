#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROOMS 100
#define MAX_CUSTOMERS 100
#define MAX_NAME_LEN 50
#define DELUXE_PRICE 1000000
#define EXECUTIVE_PRICE 3000000
#define PRESIDENTIAL_PRICE 20000000

typedef enum {
    DELUXE,
    EXECUTIVE,
    PRESIDENTIAL
} RoomType;

typedef struct {
    int roomNumber;
    RoomType type;
    int isAvailable;
} Room;

typedef struct {
    char name[MAX_NAME_LEN];
    char email[MAX_NAME_LEN];
    int roomNumber;
    int nights;
    int numberOfGuests;
    float totalBill;
    RoomType roomType;
} Customer;

Room rooms[MAX_ROOMS];
Customer customers[MAX_CUSTOMERS];
int currentCustomers = 0;

void initializeRooms() {
    int i;
    for (i = 0; i < 70; i++) {
        rooms[i].roomNumber = i + 1;
        rooms[i].type = DELUXE;
        rooms[i].isAvailable = 1;
    }
    for (; i < 95; i++) {
        rooms[i].roomNumber = i + 1;
        rooms[i].type = EXECUTIVE;
        rooms[i].isAvailable = 1;
    }
    for (; i < MAX_ROOMS; i++) {
        rooms[i].roomNumber = i + 1;
        rooms[i].type = PRESIDENTIAL;
        rooms[i].isAvailable = 1;
    }
}

float getRoomPrice(RoomType type) {
    switch (type) {
        case DELUXE: return DELUXE_PRICE;
        case EXECUTIVE: return EXECUTIVE_PRICE;
        case PRESIDENTIAL: return PRESIDENTIAL_PRICE;
        default: return 0;
    }
}

const char* getRoomTypeName(RoomType type) {
    switch (type) {
        case DELUXE: return "Deluxe";
        case EXECUTIVE: return "Executive";
        case PRESIDENTIAL: return "Presidential";
        default: return "Unknown";
    }
}

void listAvailableRoomsByType(RoomType type) {
    printf("Kamar yang tersedia (%s):\n", getRoomTypeName(type));
    for (int i = 0; i < MAX_ROOMS; i++) {
        if (rooms[i].isAvailable && rooms[i].type == type) {
            printf("Kamar %d\n", rooms[i].roomNumber);
        }
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
    RoomType roomType = rooms[roomNumber - 1].type;
    strcpy(customers[currentCustomers].name, name);
    strcpy(customers[currentCustomers].email, email);
    customers[currentCustomers].roomNumber = roomNumber;
    customers[currentCustomers].nights = nights;
    customers[currentCustomers].numberOfGuests = numberOfGuests;
    customers[currentCustomers].roomType = roomType;
    customers[currentCustomers].totalBill = nights * getRoomPrice(roomType);
    currentCustomers++;
    printf("Pelanggan berhasil ditambahkan!\n");
}

void checkOutCustomer(int roomNumber) {
    for (int i = 0; i < currentCustomers; i++) {
        if (customers[i].roomNumber == roomNumber) {
            printf("Total tagihan untuk kamar %d: %.2f juta rupiah\n", roomNumber, customers[i].totalBill / 1000000);
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
            printf("Kamar %d (%s)\n", rooms[i].roomNumber, 
                   rooms[i].type == DELUXE ? "Deluxe" :
                   rooms[i].type == EXECUTIVE ? "Executive" : "Presidential");
        }
    }
}

void listCustomers() {
    printf("Pelanggan saat ini:\n");
    for (int i = 0; i < currentCustomers; i++) {
        printf("Nama: %s, Email: %s, Kamar: %d (%s), Malam: %d, Jumlah Tamu: %d, Tagihan: %.2f juta rupiah\n",
               customers[i].name, customers[i].email, customers[i].roomNumber,
               getRoomTypeName(customers[i].roomType),
               customers[i].nights, customers[i].numberOfGuests, customers[i].totalBill / 1000000);
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

int selectRoomType() {
    int roomType;
    printf("Pilih tipe kamar:\n");
    printf("1. Deluxe\n");
    printf("2. Executive\n");
    printf("3. Presidential\n");
    printf("Masukkan pilihan Anda: ");
    scanf("%d", &roomType);
    return roomType - 1; // Mengurangi 1 untuk menyesuaikan dengan enum RoomType
}

int selectRoom(RoomType roomType) {
    int roomNumber;
    listAvailableRoomsByType(roomType);
    printf("Masukkan nomor kamar yang dipilih: ");
    scanf("%d", &roomNumber);
    return roomNumber;
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
                printf("Masukkan jumlah tamu (maks 2): ");
                scanf("%d", &numberOfGuests);
                if (numberOfGuests > 2) {
                    printf("Jumlah tamu per kamar tidak boleh lebih dari 2!\n");
                    break;
                }
                printf("Masukkan nama pelanggan: ");
                scanf("%s", name);
                printf("Masukkan email pelanggan: ");
                scanf("%s", email);
                int roomType = selectRoomType();
                if (roomType < 0 || roomType > 2) {
                    printf("Pilihan tipe kamar tidak valid!\n");
                    break;
                }
                roomNumber = selectRoom((RoomType)roomType);
                printf("Masukkan jumlah malam menginap: ");
                scanf("%d", &nights);
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