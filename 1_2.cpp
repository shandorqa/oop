#include <iostream>
#include <fstream>
#include <cstring>  // Для strcpy, strtok, atoi
#include <cstdlib>  // Для malloc, free

struct Hotel {
    char name[32];
    int stars;
    char address[64];
    char phone[20];
    int rooms;
    int lux_rooms;
    int free_rooms;
};

struct HotelList {
    Hotel* hotels;
    int nhotels;
    int alloc;
};

void initHotelList(HotelList* list) {
    list->hotels = nullptr;
    list->nhotels = 0;
    list->alloc = 0;
}

void reallocHotelList(HotelList* list, int new_alloc) {
    Hotel* new_hotels = (Hotel*)malloc(new_alloc * sizeof(Hotel));
    for (int i = 0; i < list->nhotels; ++i) {
        new_hotels[i] = list->hotels[i];
    }
    free(list->hotels);
    list->hotels = new_hotels;
    list->alloc = new_alloc;
}

void freeHotelList(HotelList* list) {
    if (list->hotels) {
        free(list->hotels);
    }
    initHotelList(list);
}

void inputHotel(Hotel* hotel) {
    std::cout << "Name       -> ";
    std::cin.getline(hotel->name, 32);
    std::cout << "Stars      -> ";
    std::cin >> hotel->stars;
    std::cin.ignore();
    std::cout << "Address    -> ";
    std::cin.getline(hotel->address, 64);
    std::cout << "Phone      -> ";
    std::cin.getline(hotel->phone, 20);
    std::cout << "Rooms      -> ";
    std::cin >> hotel->rooms;
    std::cout << "Lux Rooms  -> ";
    std::cin >> hotel->lux_rooms;
    std::cout << "Free Rooms -> ";
    std::cin >> hotel->free_rooms;
    std::cin.ignore();
}

void printHotel(const Hotel* hotel) {
    std::cout << "Name       -> " << hotel->name << "\n";
    std::cout << "Stars      -> " << hotel->stars << "\n";
    std::cout << "Address    -> " << hotel->address << "\n";
    std::cout << "Phone      -> " << hotel->phone << "\n";
    std::cout << "Rooms      -> " << hotel->rooms << "\n";
    std::cout << "Lux Rooms  -> " << hotel->lux_rooms << "\n";
    std::cout << "Free Rooms -> " << hotel->free_rooms << "\n";
}

void addHotel(HotelList* list) {
    if (list->alloc == 0) {
        reallocHotelList(list, 1);
    } else if (list->nhotels == list->alloc) {
        reallocHotelList(list, list->alloc * 2);
    }
    inputHotel(&list->hotels[list->nhotels]);
    ++list->nhotels;
    std::cout << "\n[OK] Hotel was added\n\n";
}

void printHotels(const HotelList* list) {
    if (list->nhotels == 0) {
        std::cout << "\n[OK] Hotel list is empty\n\n";
        return;
    }

    std::cout << "\n[OK] Hotel list:\n";
    for (int i = 0; i < list->nhotels; ++i) {
        std::cout << "Hotel #" << (i + 1) << ":\n";
        printHotel(&list->hotels[i]);
        std::cout << "\n";
    }
}

void removeHotelByIndex(HotelList* list, int index) {
    if (index < 1 || index > list->nhotels) {
        std::cout << "\n[FAIL] No hotel with such number\n\n";
        return;
    }
    for (int i = index - 1; i < list->nhotels - 1; ++i) {
        list->hotels[i] = list->hotels[i + 1];
    }
    --list->nhotels;
    std::cout << "\n[OK] Hotel successfully removed\n\n";
}

void printBestHotel(const HotelList* list) {
    if (list->nhotels == 0) {
        std::cout << "\n[OK] Hotel list is empty\n\n";
        return;
    }

    const Hotel* bestHotel = nullptr;
    for (int i = 0; i < list->nhotels; ++i) {
        if (!bestHotel || list->hotels[i].free_rooms > bestHotel->free_rooms ||
            (list->hotels[i].free_rooms == bestHotel->free_rooms && list->hotels[i].stars > bestHotel->stars)) {
            bestHotel = &list->hotels[i];
        }
    }

    std::cout << "\n[OK] Best hotel with most free rooms:\n";
    printHotel(bestHotel);
    std::cout << "\n";
}

void readFromFile(HotelList* list, const char* filename) {
    std::ifstream file(filename);
    if (!file) {
        return;
    }

    char line[256];
    while (file.getline(line, 256)) {
        if (strlen(line) == 0) {
            break;
        }
        if (list->nhotels == list->alloc) {
            reallocHotelList(list, list->alloc == 0 ? 1 : list->alloc * 2);
        }
        char* token = strtok(line, "|");
        strcpy(list->hotels[list->nhotels].name, token);

        token = strtok(NULL, "|");
        list->hotels[list->nhotels].stars = atoi(token);

        token = strtok(NULL, "|");
        strcpy(list->hotels[list->nhotels].address, token);

        token = strtok(NULL, "|");
        strcpy(list->hotels[list->nhotels].phone, token);

        token = strtok(NULL, "|");
        list->hotels[list->nhotels].rooms = atoi(token);

        token = strtok(NULL, "|");
        list->hotels[list->nhotels].lux_rooms = atoi(token);

        token = strtok(NULL, "|");
        list->hotels[list->nhotels].free_rooms = atoi(token);

        ++list->nhotels;
    }
    file.close();
}

void saveToFile(const HotelList* list, const char* filename) {
    std::ofstream file(filename);
    for (int i = 0; i < list->nhotels; ++i) {
        file << list->hotels[i].name << "|" << list->hotels[i].stars << "|"
             << list->hotels[i].address << "|" << list->hotels[i].phone << "|"
             << list->hotels[i].rooms << "|" << list->hotels[i].lux_rooms << "|"
             << list->hotels[i].free_rooms << "\n";
    }
    file.close();
}

void printMenu() {
    std::cout << "[1] Add hotel\n";
    std::cout << "[2] Print hotels\n";
    std::cout << "[3] Remove hotel by number\n";
    std::cout << "[4] Best Hotel with most free rooms\n";
    std::cout << "[0] Exit\n";
    std::cout << " -> ";
}

int main() {
    HotelList hotelList;
    initHotelList(&hotelList);

    const char* filename = "store.txt";
    readFromFile(&hotelList, filename);

    int command, number;
    do {
        printMenu();
        std::cin >> command;
        std::cin.ignore();

        if (command == 1) {
            addHotel(&hotelList);
        } else if (command == 2) {
            printHotels(&hotelList);
        } else if (command == 3) {
            std::cout << "\nEnter number -> ";
            std::cin >> number;
            std::cin.ignore();
            removeHotelByIndex(&hotelList, number);
        } else if (command == 4) {
            printBestHotel(&hotelList);
        } else if (command == 0) {
            std::cout << "\n[OK] Bye\n\n";
        } else {
            std::cout << "\n[FAIL] Wrong command!\n\n";
        }
    } while (command != 0);

    saveToFile(&hotelList, filename);
    freeHotelList(&hotelList);

    return 0;
}
