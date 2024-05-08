#include <iostream>
#include <fstream>

bool isDigitC(const char*& arr) {
	return *arr >= '0' && *arr <= '9';
}

bool isLetterC(const char*& arr) {
	return *arr >= 'A' && *arr <= 'E';
}

bool isIdentifierC(const char*& arr) {
	return isLetterC(arr);
}

bool isUIntM(const char*& arr, bool flag = false)
{
	if (isDigitC(arr))
	{
		arr++;
		flag = true;
		return isUIntM(arr, flag);
	}
	return flag;
}

bool isExpressionM(const char*&, bool);

bool isMultiplierM(const char*& arr) {
	if (*arr == '(') {
		arr++;
		if (isExpressionM(arr, true)) {
			return *(arr++) == ')';
		}
	}
	if (isIdentifierC(arr)) {
		arr++;
		return true;
	}
	if (isUIntM(arr)) {
		return true;
	}
	return false;
}

bool isTermM(const char*& arr) {
	if (isMultiplierM(arr)) {
		if (*arr == '*') {
			arr++;
			return isTermM(arr);
		}
		else {
			return true;
		}
	}
	return false;
}

bool isExpressionM(const char*& arr, bool braced = false) {
	if (isTermM(arr)) {
		if (*arr == '+' || *arr == '-') {
			arr++;
			return isExpressionM(arr, braced);
		}
		if (*arr == ')' && braced) {
			return true;
		}
		return *arr == '\0';
	}
	return false;
}

int main() {

	setlocale(LC_ALL, "Russian");
	const int MAX_STR_LENGTH = 100;
	char* strf = new char[MAX_STR_LENGTH];
	std::ifstream ifs("input.txt");
	try {
		if (!ifs.good()) {
			throw "Файл ввода недоступен. Завершение программы...";
		}
	}
	catch (const char* e) {
		std::cerr << e;
		return 1;
	}

	std::cout << "Reading input from file...\n";
	while (ifs) {
		ifs.getline(strf, MAX_STR_LENGTH);
		const char* str = strf;
		const char* strBuf = str;
		std::cout << (isExpressionM(str) ? "TRUE" : "FALSE") << '\t' << strBuf << "\n";
	}
}
