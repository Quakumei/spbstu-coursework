#include <iostream>
#include<ctime>
#include<cstdlib>
#include<fstream>

#define RANDOM_LIMIT 10
#define FILENAME "arrays.txt"

template <typename Type>
void printArray(Type& a, size_t N)
{
    for (int i = 0; i < N; i++) 
    {
        std::cout << a[i] << " ";
    }
    std::cout << '\n';
}

template <typename T>
void swap(T& a, T& b)
{
    T temp = a;
    a = b;
    b = temp;
}


void intArrayTransform(int a[], size_t N) 
{
    /* преобразовывает массив целых чисел таким образом,
    чтобы с начала располагались чётные элементы, а потом нечётные */

    int j = N-1;
    for (int i = 0; i < j ; i++) 
    {
        if (abs(a[i]) % 2 == 1) 
        {
            while (j > i && abs(a[j]) % 2 == 1) {
                j--; //Идём к следующему чётному с конца
            }
            swap(a[i], a[j]);
            j--;
        }
    }
    
}

int main()
{
    setlocale(LC_ALL, "Russian");

    // 1
    std::cout << "Заданный заранее массив:\n";
    int a[] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18 };
    size_t aSize = sizeof(a) / sizeof(a[0]);
    printArray(a, aSize);
    intArrayTransform(a, aSize);
    printArray(a, aSize);

    //2
    std::cout << "\nВведите длину случайного массива: ";
    int bSize = 0;
    std::cin >> bSize;
    if (bSize <= 0 || !std::cin.good()) {
        std::cerr << "Размер массива задан неверно. Завершение программы...\n";
        return 1;
    }

    srand(time(0));
    int* b = new int[bSize];
    for (int i = 0; i < bSize; i++) {
        b[i] = rand() % (RANDOM_LIMIT*2) - RANDOM_LIMIT;
    }
    printArray(b,bSize);
    intArrayTransform(b, bSize);
    printArray(b, bSize);

    //3
    std::cout << "\nИз файла...\n";
    std::ifstream fin(FILENAME);
    if (!fin.good()) {
        std::cerr << "Ошибка открытия файла. Завершение программы...\n";
        return 1;
    }
    std::cout << "==============================\n";
    while (!fin.eof()) {
        int cSize = -1;
        fin >> cSize;
        if (cSize <= 0 || !fin.good()) {
            std::cerr << "Размер массива задан неверно. Завершение программы...\n";
            return 1;
        }
        int* c = new int[cSize];
        for (int i = 0; i < cSize; i++) {
            fin >> c[i];
            if (fin.eof()) {
                std::cerr << "Неожиданный конец файла при чтении массива. Завершение программы...\n";
                return 1;
            }
            if (!fin.good()) {
                std::cerr << "Неправильный ввод элемента массива. Завершение программы...\n";
                return 1;
            }
        }
        printArray(c, cSize);
        intArrayTransform(c, cSize);
        printArray(c, cSize);
        std::cout << "==============================\n";
    }   
}
