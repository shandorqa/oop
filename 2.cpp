#include <iostream>
#include <cstring>
#include <fstream>
#include <iomanip>

// Класс для ввода номера телефона
class PhoneNumber {
private:
    char number[20]; // Хранит полный номер телефона с +7
public:
    // Конструктор по умолчанию
    PhoneNumber() {
        strcpy(number, "+");
    }
    // Параметрический конструктор
    PhoneNumber(const char* number_) {
        strcpy(number, number_);
    }
    //  Ввод номера телефона от юзера
    void input() {
        bool valid = false;
        char phone[20];
        while (!valid) {
            std::cout << "Введите 10-значный номер телефона (без +7): ";
            std::cin >> phone;
            if (strlen(phone) != 10) {
                std::cout << "Ошибка: необходимо ввести ровно 10 цифр.\n";
                continue;
            }
            valid = true;
            for (int i = 0; i < 10; ++i) {
                if (!isdigit(phone[i])) {
                    std::cout << "Ошибка: номер телефона должен содержать только цифры.\n";
                    valid = false;
                    break;
                }
            }
        }
        char fullPhone[20] = "+7";
        strcat(fullPhone, phone);
        strcpy(number, fullPhone);
    }
    // Вывод номера телефона
    void print() const {
        std::cout << number;
    }
    // Геттер для получения номера телефона
    const char* getNumber() const {
        return number;
    }
};

// Класс отель
class Hotel {
private:
    char name[100];
    int stars;
    char address[100];
    PhoneNumber phone; // Включает класс PhoneNumber
    int rooms;
    int lux_rooms;
    int free_rooms;
public:
    // Конструктор по умолчанию
    Hotel() {
        strcpy(name, "");
        stars = 0;
        strcpy(address, "");
        rooms = 0;
        lux_rooms = 0;
        free_rooms = 0;
    }
    // Параметрический конструктор
    Hotel(const char* name_, int stars_, const char* address_, const PhoneNumber& phone_, int rooms_, int lux_rooms_, int free_rooms_)
        : phone(phone_) {
        strcpy(name, name_);
        stars = stars_;
        strcpy(address, address_);
        rooms = rooms_;
        lux_rooms = lux_rooms_;
        free_rooms = free_rooms_;
    }

    // Конструктор копирования
    Hotel(const Hotel& other)
        : phone(other.phone) {
        strcpy(name, other.name);
        stars = other.stars;
        strcpy(address, other.address);
        rooms = other.rooms;
        lux_rooms = other.lux_rooms;
        free_rooms = other.free_rooms;
    }

    // Ввод данных об отеле
    void input() {
        std::cout << "Введите название отеля: ";
        std::cin.ignore();
        std::cin.getline(name, 100);

        do {
            std::cout << "Введите количество звезд (1-5): ";
            std::cin >> stars;
            if (stars < 1 || stars > 5) {
                std::cout << "Ошибка: количество звезд должно быть от 1 до 6.\n";
            }
        } while (stars < 1 || stars > 5);

        std::cin.ignore();
        std::cout << "Введите адрес: ";
        std::cin.getline(address, 100);
        phone.input();

        do {
            std::cout << "Введите общее количество номеров: ";
            std::cin >> rooms;
            if (rooms < 0) {
                std::cout << "Ошибка: количество номеров не может быть отрицательным.\n";
            }
        } while (rooms < 0);

        do {
            std::cout << "Введите количество номеров люкс: ";
            std::cin >> lux_rooms;
            if (lux_rooms < 0 || lux_rooms > rooms) {
                std::cout << "Ошибка: количество номеров люкс не может быть отрицательным и не может превышать общее количество номеров.\n";
            }
        } while (lux_rooms < 0 || lux_rooms > rooms);

        do {
            std::cout << "Введите количество свободных номеров: ";
            std::cin >> free_rooms;
            if (free_rooms < 0 || free_rooms > rooms) {
                std::cout << "Ошибка: количество свободных номеров не может быть отрицательным и не может превышать общее количество номеров.\n";
            }
        } while (free_rooms < 0 || free_rooms > rooms);
    }

    // Вывод данных об лучшем отеле
    void print() const {
        std::cout << "Название отеля: " << name << "\n";
        std::cout << "Звезды: " << stars << "\n";
        std::cout << "Адрес: " << address << "\n";
        std::cout << "Телефон: ";
        phone.print();
        std::cout << "\n";
        std::cout << "Всего номеров: " << rooms << "\n";
        std::cout << "Номеров люкс: " << lux_rooms << "\n";
        std::cout << "Свободных номеров: " << free_rooms << "\n";
    }

    // Геттеры для доступа к приватным членам
    const char* getName() const { return name; }
    int getStars() const { return stars; }
    const char* getAddress() const { return address; }
    const PhoneNumber& getPhone() const { return phone; }
    int getRooms() const { return rooms; }
    int getLuxRooms() const { return lux_rooms; }
    int getFreeRooms() const { return free_rooms; }

    // Переопределение оператора присваивания
    Hotel& operator=(const Hotel& other) {
        if (this != &other) {
            strcpy(name, other.name);
            stars = other.stars;
            strcpy(address, other.address);
            phone = other.phone;
            rooms = other.rooms;
            lux_rooms = other.lux_rooms;
            free_rooms = other.free_rooms;
        }
        return *this;
    }
};

// Класс для управления отелями
class HotelManager {
private:
    static const int MAX_HOTELS = 50;
    Hotel hotelList[MAX_HOTELS];
    int nhotels;

public:
    // Конструктор по умолчанию
    HotelManager() {
        nhotels = 0;
    }

    // Функция для добавления отеля
    void addHotel() {
        if (nhotels < MAX_HOTELS) {
            hotelList[nhotels].input();
            nhotels++;
            std::cout << "\nОтель добавлен\n";
        } else {
            std::cout << "\nНевозможно, лимит!\n";
        }
    }

    // Функция для вывода всех отелей
    void printHotels() const {
        if (nhotels == 0) {
            std::cout << "\nНет доступных отелей\n";
            return;
        }
        // Заголовок таблицы
        std::cout << std::left
                  << std::setw(5) << "№"
                  << std::setw(20) << "Название"
                  << std::setw(7) << "Звезды"
                  << std::setw(30) << "Адрес"
                  << std::setw(20) << "Телефон"
                  << std::right
                  << std::setw(10) << "Номера"
                  << std::setw(12) << "Люкс"
                  << std::setw(12) << "Свободные"
                  << "\n";
        // Разделитель
        std::cout << std::string(86, '-') << "\n";
        // Вывод данных отелей
        for (int i = 0; i < nhotels; ++i) {
            // Получаем данные об отеле, ограничивая строки фиксированной длиной
            std::string hotelName = std::string(hotelList[i].getName()).substr(0, 14); // Макс. 14 символов
            std::string hotelAddress = std::string(hotelList[i].getAddress()).substr(0, 19); // Макс. 19 символов
            std::string phone = std::string(hotelList[i].getPhone().getNumber()).substr(0, 14); // Макс. 14 символов

            std::cout << std::left
                      << std::setw(4) << (i + 1)                       // №
                      << std::setw(15) << hotelName                    // Название
                      << std::setw(6) << hotelList[i].getStars()       // Звезды
                      << std::setw(20) << hotelAddress                 // Адрес
                      << std::setw(15) << phone;                       // Телефон

            std::cout << std::right
                      << std::setw(8) << hotelList[i].getRooms()       // Всего номеров
                      << std::setw(8) << hotelList[i].getLuxRooms()    // Номера люкс
                      << std::setw(10) << hotelList[i].getFreeRooms()  // Свободные номера
                      << "\n";
        }
    }

    // Delete отеля по индексу
    void removeHotel(int index) {
        if (index < 1 || index > nhotels) {
            std::cout << "\nНеверный номер отеля!\n";
            return;
        }
        for (int i = index - 1; i < nhotels - 1; ++i) {
            hotelList[i] = hotelList[i + 1];
        }
        nhotels--;
        std::cout << "\nОтель успешно удален!\n";
    }

    // Read отелей из файла
    void readFromFile() {
        std::ifstream file("store.txt");
        if (!file) return;

        nhotels = 0;
        while (nhotels < MAX_HOTELS && file.peek() != EOF) {
            char name[100], address[100], phoneStr[20];
            int stars, rooms, lux_rooms, free_rooms;
            file.getline(name, 100, '|');
            file >> stars;
            file.ignore(1, '|');
            file.getline(address, 100, '|');
            file.getline(phoneStr, 20, '|');
            file >> rooms;
            file.ignore(1, '|');
            file >> lux_rooms;
            file.ignore(1, '|');
            file >> free_rooms;
            file.ignore();
            if (file.fail()) break;
            PhoneNumber phone(phoneStr);
            hotelList[nhotels] = Hotel(name, stars, address, phone, rooms, lux_rooms, free_rooms);
            nhotels++;
        }
        file.close();
    }

    // Save отелей в файл
    void saveToFile() const {
        std::ofstream file("store.txt");
        for (int i = 0; i < nhotels; ++i) {
            file << hotelList[i].getName() << "|"
                 << hotelList[i].getStars() << "|"
                 << hotelList[i].getAddress() << "|"
                 << hotelList[i].getPhone().getNumber() << "|"
                 << hotelList[i].getRooms() << "|"
                 << hotelList[i].getLuxRooms() << "|"
                 << hotelList[i].getFreeRooms() << "\n";
        }
        file.close();
    }

    // Отображение best отеля
    void showBestHotel() const {
        if (nhotels == 0) {
            std::cout << "\nНет доступных отелей!\n";
            return;
        } else {
            int best_index = 0;
            for (int i = 1; i < nhotels; ++i) {
                if (hotelList[i].getFreeRooms() > hotelList[best_index].getFreeRooms()) {
                    best_index = i;
                } else if (hotelList[i].getFreeRooms() == hotelList[best_index].getFreeRooms() &&
                           hotelList[i].getStars() > hotelList[best_index].getStars()) {
                    best_index = i;
                }
            }
            std::cout << "\nЛучший отель с наибольшим количеством свободных номеров:\n";
            hotelList[best_index].print();
        }
    }
};

// Функция для вывода меню
void printMenu() {
    std::cout << "[1] Добавить отель\n";
    std::cout << "[2] Показать все отели\n";
    std::cout << "[3] Удалить отель по индексу\n";
    std::cout << "[4] Показать лучший отель\n";
    std::cout << "[0] Выход\n";
    std::cout << "Выберите опцию: ";
}

// Главная функция
int main() {
    HotelManager manager;
    manager.readFromFile();
    int command;

    do {
        printMenu();
        std::cin >> command;

        if (command == 1) {
            manager.addHotel();
        } else if (command == 2) {
            manager.printHotels();
        } else if (command == 3) {
            int number;
            std::cout << "Введите номер отеля: ";
            std::cin >> number;
            manager.removeHotel(number);
        } else if (command == 4) {
            manager.showBestHotel();
        }
    } while (command != 0);

    manager.saveToFile();
    std::cout << "\nBB!\n";
    return 0;
}
