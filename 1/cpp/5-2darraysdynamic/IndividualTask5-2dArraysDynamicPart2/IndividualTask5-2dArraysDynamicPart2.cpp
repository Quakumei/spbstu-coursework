#include <iostream>
#include <fstream>
#include <iomanip>

#define FILE_INPUT_DYNAMIC "dynamic_arrays_in.txt"
#define FILE_OUTPUT_DYNAMIC "dynamic_arrays_out.txt"

void fillSpiralClockwise(int** destinationArray, int size) {
	int nextN = 1;
	int margin = 0;
	int halfsize = size / 2;
	while (margin < halfsize) {
		for (int i = 0 + margin; i < size-1-margin; i++) {
			destinationArray[0 + margin][i] = nextN;
			nextN++;
		}
		for (int j = 0+ margin; j < size-1-margin; j++) {
			destinationArray[j][size - 1 - margin] = nextN;
			nextN++;
		}
		for (int i = size - 1 - margin; i > 0+margin; i--) {
			destinationArray[size - 1 - margin][i] = nextN;
			nextN++;
		}
		for (int j = size - 1 - margin; j >= 1+margin; j--) {
			destinationArray[j][0 + margin] = nextN;
			nextN++;
		}
		margin += 1;
	}
	if (halfsize*2 != size){
		destinationArray[margin][margin] = nextN; // middle
	}
	//std::clog << "final: " << nextN << "\n\n";
}

void printSquareMatrix(int ** array, const int size, std::ostream& os = std::cout) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			os << std::setw(4) << array[i][j];
		}
		os << '\n';
	}
	os << '\n';
}

int main() {


	setlocale(LC_ALL, "Russian");
	std::cout << "Встроенные массивы из файла: \n\n";
	try {
		std::ifstream ifs(FILE_INPUT_DYNAMIC);
		std::ofstream ofs(FILE_OUTPUT_DYNAMIC);
		if (!ifs.good()) {
			throw "Файл ввода недоступен. Завершение программы...";
		}
		if (!ofs.good()) {
			throw "Файл вывода недоступен. Завершение программы...";
		}

		while (!ifs.eof()) {

			int size = 0;
			ifs >> size;
			if (!ifs.good() && !ifs.eof()) {
				throw "Ошибка ввода размера массива. Завершение программы...";
			}
			else if (size <= 0) {
				throw "Размер массива задан некорректно. Завершение программы...";
			}
			
			int** matrix = new int* [size];
			for (int i = 0; i < size; ++i)
			{
				matrix[i] = new int[size];
			}

			fillSpiralClockwise(matrix, size);

			printSquareMatrix(matrix, size, std::cout);
			printSquareMatrix(matrix, size, ofs);

			for (int i = 0; i < size; i++) {
				delete[] matrix[i];
			}
			delete[] matrix;
		}
	}
	catch (const char* what) {
		std::cerr << what;
		return 1;
	}
	return 0;
}