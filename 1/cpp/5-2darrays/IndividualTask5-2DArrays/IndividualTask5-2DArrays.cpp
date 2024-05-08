#include <iostream>
#include <fstream>
#include <iomanip>

#define FILE_INPUT_REGULAR "regular_arrays_in.txt"
#define FILE_OUTPUT_REGULAR "regular_arrays_out.txt"


int getCountZeroInColumnAny(const int* array, int nRow, int nColumn) {
	int counter = 0;
	for (int j = 0; j < nRow; j++) {
		for (int i = 0; i < nColumn; i++) {
			if (*(array + i*nRow + j) == 0) {
				counter += 1;
				break;
			}
		}
	}
	return counter;
}

void read2dArray(int* destination, const int nRow, const int nColumn, std::ifstream& ifs) {
	for (int i = 0; i < nRow; i++) {
		for (int j = 0; j < nColumn; j++) {
			if (!ifs.good()) {
				throw "Ошибка ввода элемента массива. Завершение программы...";
			}
			ifs >> *(destination + nRow * i + j);
		}
	}
}

void print2dArray(const int* array, const int nRow, const int nColumn, std::ostream& os = std::cout) {
	for (int i = 0; i < nRow; i++) {
		for (int j = 0; j < nColumn; j++) {
			os << std::setw(4) << *(array + nRow * i + j);
		}
		os << '\n';
	}
}

int main() {
	setlocale(LC_ALL, "Russian");
	std::cout << "Встроенные массивы из файла: \n\n";
	const int BIG_SIZE = 100;
	int matrix[BIG_SIZE][BIG_SIZE] = {};
	try {
		std::ifstream ifs(FILE_INPUT_REGULAR);
		std::ofstream ofs(FILE_OUTPUT_REGULAR);
		if (!ifs.good()) {
			throw "Файл ввода недоступен. Завершение программы...";
		}
		if (!ofs.good()) {
			throw "Файл вывода недоступен. Завершение программы...";
		}

		while (!ifs.eof()) {

			int nRow = 0;
			ifs >> nRow;
			if (ifs.eof() || !ifs.good()) {
				throw "Ошибка ввода размера массива. Завершение программы...";
			}
			else if (nRow <= 0) {
				throw "Размер массива задан некорректно. Завершение программы...";
			}
			int nColumn = 0;
			ifs >> nColumn;
			if (ifs.eof() || !ifs.good()) {
				throw "Ошибка ввода размера массива. Завершение программы...";
			}
			else if (nColumn <= 0) {
				throw "Размер массива задан некорректно. Завершение программы...";
			}

			read2dArray(matrix[0], nRow, nColumn, ifs);
			print2dArray(matrix[0], nRow, nColumn, std::cout);
			int result = getCountZeroInColumnAny(matrix[0], nRow, nColumn);
			std::cout << "result: " << result << "\n\n";
			ofs << result << '\n';
		}
	}
	catch (const char* what) {
		std::cerr << what;
		return 1;
	}
	return 0;
}