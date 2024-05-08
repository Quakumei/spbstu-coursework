//вар5 тампио 3530904/10002
#include <iostream>
#include <fstream>

#define IFNAME "input.txt"
#define OFNAME "output.txt"

char* getDiff(char* destination, const char* source_a, const char* source_b) {
    int j = 0;
    int map[255] = {};
    for (int i = 0; source_a[i] != '\0'; i++) {
        int charIndex = static_cast<int>(source_a[i]);
        if (map[charIndex] == 0) {
            map[charIndex] = 1; //Встретился только в 1 строке но не в обеих 
        }
    }
    for (int i = 0; source_b[i] != '\0'; i++) {
        int charIndex = static_cast<int>(source_b[i]);
        if (map[charIndex] == 1) {
            map[charIndex] = 3; //Общие
        }
        else if (map[charIndex] == 0) {
            map[charIndex] = 2; //Встретилось только в 2 строке но не в обеих 
        }
    }
    for (int i = 0; i < 256; i++){
        if (map[i] < 3 && map[i] > 0) {
            if (destination[j] == '\0') {
                throw "Недостаточно памяти в destination строке. Завершение программы...";
            }
            destination[j] = static_cast<char>(i);
            j++;
        }
    }
    destination[j] = '\0';
    return destination;
}

int main()
{
    setlocale(LC_ALL, "RUSSIAN");
    std::cout << "\nИз файла...\n";
    try {
        std::ifstream fin(IFNAME);
        std::ofstream fout(OFNAME);
        if (!fin.good() || !fout.good()) {
            throw "Ошибка открытия файла. Завершение программы...\n";
        }
        while (!fin.eof()) {
            int arraySize = -1;
            fin >> arraySize;
            if (arraySize <= 0 || !fin.good()) {
                throw "Размер массива1 задан неверно. Завершение программы...\n";
            }
            fin.ignore();

            char* charArrayA = new char[arraySize + 1];
            charArrayA[arraySize] = '\0';
            char* charArrayB = new char[arraySize + 1];
            charArrayB[arraySize] = '\0';

            if (fin.eof()) {
                throw "Неожиданный конец файла при чтении массива1. Завершение программы...\n";
            }
            fin.getline(charArrayA, arraySize + 1,'\n');
                        
            if (fin.eof()) {
                throw "Неожиданный конец файла при чтении массива2. Завершение программы...\n";
            }
            fin.getline(charArrayB, arraySize + 1, '\n');
            

            int arraySizeSum = arraySize * 2;
            const int ASCII_SIZE = 255;
            int smallestSize = (arraySizeSum < ASCII_SIZE) ? arraySizeSum : ASCII_SIZE;
            char* destinationCharArray = new char[smallestSize + 1];
            for (int i = 0; i < smallestSize; i++) {
                destinationCharArray[i] = ':';
            }
            destinationCharArray[smallestSize] = '\0';

            getDiff(destinationCharArray, charArrayA, charArrayB);
            fout << destinationCharArray << '\n';

            // LOG
            std::clog << "=============================\n";
            std::clog << charArrayA << "\\0\n";
            std::clog << charArrayB << "\\0\n";
            std::clog << destinationCharArray << "\\0\n";


            delete[] charArrayA;
            delete[] charArrayB;
            delete[] destinationCharArray;
        }
    }
    catch (const char* error) {
        std::cerr << error;
        return 1;
    }

    return 0;
}