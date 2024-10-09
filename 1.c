#include <iostream>
#include <iomanip>  // Для управления выводом таблицы
#include <cstring>
#include <fstream>

struct Hotel {
    char name[100];
    int stars;
    char address[100];
    char phone[20];
    int rooms;
    int lux_rooms;
    int free_rooms;
};

Hotel hotelList[10];
int nhotels = 0;

void inputHotel(Hotel& hotel) {
    std::cout << "Enter hotel name: ";
    std::cin.ignore();
    std::cin.getline(hotel.name, 100);
    std::cout << "Enter stars: ";
    std::cin >> hotel.stars;
    std::cin.ignore();
    std::cout << "Enter address: ";
    std::cin.getline(hotel.address, 100);
    std::cout << "Enter phone: ";
    std::cin.getline(hotel.phone, 20);
    std::cout << "Enter total rooms: ";
    std::cin >> hotel.rooms;
    std::cout << "Enter luxury rooms: ";
    std::cin >> hotel.lux_rooms;
    std::cout << "Enter free rooms: ";
    std::cin >> hotel.free_rooms;
}

void printHotels() {
    if (nhotels == 0) {
        std::cout << "\nNo hotels available!\n";
        return;
    }
    
    std::cout << std::setw(4) << "No" << " | "
              << std::setw(20) << "Hotel Name" << " | "
              << std::setw(6) << "Stars" << " | "
              << std::setw(25) << "Address" << " | "
              << std::setw(15) << "Phone" << " | "
              << std::setw(6) << "Rooms" << " | "
              << std::setw(6) << "Lux" << " | "
              << std::setw(6) << "Free" << "\n";
    
    std::cout << std::string(101, '-') << "\n";  // Разделительная линия
    
    for (int i = 0; i < nhotels; ++i) {
        std::cout << std::setw(4) << i + 1 << " | "
                  << std::setw(20) << hotelList[i].name << " | "
                  << std::setw(6) << hotelList[i].stars << " | "
                  << std::setw(25) << hotelList[i].address << " | "
                  << std::setw(15) << hotelList[i].phone << " | "
                  << std::setw(6) << hotelList[i].rooms << " | "
                  << std::setw(6) << hotelList[i].lux_rooms << " | "
                  << std::setw(6) << hotelList[i].free_rooms << "\n";
    }
    
    std::cout << std::string(101, '-') << "\n";  // Разделительная линия
}

void addHotel() {
    if (nhotels < 10) {
        inputHotel(hotelList[nhotels]);
        nhotels++;
        std::cout << "\nHotel added successfully!\n";
    } else {
        std::cout << "\nCannot add more hotels, limit reached!\n";
    }
}

void removeHotel(int index) {
    if (index < 1 || index > nhotels) {
        std::cout << "\nInvalid hotel number!\n";
        return;
    }
    for (int i = index - 1; i < nhotels - 1; ++i) {
        hotelList[i] = hotelList[i + 1];
    }
    nhotels--;
    std::cout << "\nHotel removed successfully!\n";
}

void printBestHotel() {
    if (nhotels == 0) {
        std::cout << "\nNo hotels available!\n";
        return;
    }

    int best_index = 0;
    for (int i = 1; i < nhotels; ++i) {
        if (hotelList[i].free_rooms > hotelList[best_index].free_rooms) {
            best_index = i;
        } else if (hotelList[i].free_rooms == hotelList[best_index].free_rooms && hotelList[i].stars > hotelList[best_index].stars) {
            best_index = i;
        }
    }
    
    std::cout << "\nBest hotel with most free rooms:\n";
    printHotels();
}

void readFromFile() {
    std::ifstream file("store.txt");
    if (!file) return;
    
    nhotels = 0;
    while (nhotels < 10 && file.peek() != EOF) {
        file.getline(hotelList[nhotels].name, 100, '|');
        file >> hotelList[nhotels].stars;
        file.ignore(1, '|');
        file.getline(hotelList[nhotels].address, 100, '|');
        file.getline(hotelList[nhotels].phone, 20, '|');
        file >> hotelList[nhotels].rooms;
        file.ignore(1, '|');
        file >> hotelList[nhotels].lux_rooms;
        file.ignore(1, '|');
        file >> hotelList[nhotels].free_rooms;
        file.ignore();

        if (file.fail()) break;
        
        nhotels++;
    }
    file.close();
}

void saveToFile() {
    std::ofstream file("store.txt");
    for (int i = 0; i < nhotels; ++i) {
        file << hotelList[i].name << "|" << hotelList[i].stars << "|" << hotelList[i].address << "|"
             << hotelList[i].phone << "|" << hotelList[i].rooms << "|" << hotelList[i].lux_rooms << "|"
             << hotelList[i].free_rooms << "\n";
    }
    file.close();
}

void printMenu() {
    std::cout << "[1] Add hotel\n";
    std::cout << "[2] Show all hotels\n";
    std::cout << "[3] Remove hotel by number\n";
    std::cout << "[4] Show best hotel\n";
    std::cout << "[0] Exit\n";
    std::cout << "Choose option: ";
}

int main() {
    readFromFile();
    int command;

    do {
        printMenu();
        std::cin >> command;
        
        if (command == 1) {
            addHotel();
        } else if (command == 2) {
            printHotels();
        } else if (command == 3) {
            int number;
            std::cout << "Enter hotel number: ";
            std::cin >> number;
            removeHotel(number);
        } else if (command == 4) {
            printBestHotel();
        }
    } while (command != 0);

    saveToFile();
    std::cout << "\nBB!\n";
    return 0;
}
