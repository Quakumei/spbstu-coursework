#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <functional>
#include <utility>

#include "Subscriber.h"
#include "myString.h"
#include "SubscriberList.h"
#include "comparators.cpp"

typedef std::string string;
//typedef myString string;

int main() {
    setlocale(LC_ALL, "ru-RU");

    try {
        std::ofstream ofs("output.txt");
        if (ofs.fail()){
            std::cerr << "Ошибка открытия файла вывода... Запись в файл производиться не будет.\n";
        }
        //Test of Subscriber
        //string name = "G.", surname = "Zho-okov", phone = "+7(960)961-11-11", tariff = "303";
        //Subscriber sub = Subscriber(name, surname, phone, tariff);
        //std::cout << "TestSub\t: " << sub << '\n';


        std::cout << "Введите имя тест-файла\n>> ";
        string filename = "1.txt";
        std::cin >> filename;
        std::ifstream ifs(filename);
        if (ifs.fail())
        {
            std::cerr << "Ошибка открытия файла ввода\n";
            return 1;
        }

        int n = 0;
        ifs >> n;
        if (n <= 0) {
            throw std::invalid_argument("Размер массив должен быть больше нуля.");
        }

        SubscriberList subList;
        for (int i = 0; i < n; i++) {
            Subscriber tempSub;
            if (ifs.eof()) {
                std::cerr << "Размер массива больше введенных данных, завершение программы\n";
                return 1;
            }
            ifs >> tempSub;
            subList.add(tempSub);
        }

        std::cout << "---- Введённый массив ----\n";
        subList.printAll(std::cout);

        bool exitFlag = false;
        while (!exitFlag) {
            std::cout << '\n' << "Выберите столбец сортировки:\n1 - Фамилия\n2 - Имя\n3 - Тариф\n4 - НомерТелефона\n5 - Имя+Фамилия\n6 - Выход\n>> ";
            int choice = 0;
            std::cin >> choice;
            switch (choice) {
            case 1:
                subList.sort(comparators[COMPARATOR_SURNAME]);
                break;
            case 2:
                subList.sort(comparators[COMPARATOR_NAME]);
                break;
            case 3:
                subList.sort(comparators[COMPARATOR_TARIFF]);
                break;
            case 4:
                subList.sort(comparators[COMPARATOR_PHONE]);
                break;
            case 5:
                subList.sort(comparators[COMPARATOR_KEY]);
                break;

            case 6:
                // exit
                return 0;
            default:
                throw std::invalid_argument("Необходимо выбрать число от 1 до 6");
            }

            ofs << "Отсортированный массив:\n";
            ofs << n << '\n';
            subList.printAll(ofs);
            subList.printAll(std::cout);

            // Counters
            int uniqueCounter = subList.countUniques();
            int severalPhonesCount = subList.countSeverals();
          
            std::cout << "\nUnique count: " << uniqueCounter << '\n';
            std::cout << "Many numbers owners: " << severalPhonesCount << '\n';
            ofs << "\nUnique count: " << uniqueCounter << '\n';
            ofs << "Many numbers owners: " << severalPhonesCount << '\n';
        }
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "invalid_argument: " << e.what() << '\n';
    }
    return 0;
}
