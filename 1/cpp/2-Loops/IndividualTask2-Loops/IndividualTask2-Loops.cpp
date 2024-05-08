#include <iostream>
#include <iomanip>
#include <cmath>

#define DELIMITER '|'
#define MARGIN 3 //Кол-во дополнительно выводимых знаков после запятой

typedef const char* InputException;
struct CalculationException {
	const char* what;
	double approxValue;
};

int calcNumbersAfterPoint(double n) {
	//Подсчитывает кол-во знаков после запятой до 30
	const int MAXCOUNTER = 30;
	int counter = 0;
	for (; int(n)!=n && counter < MAXCOUNTER; n *= 10) {
		counter++;
	}
	return counter;
}


double truncate(double value, int n) {
	//Отбрасывает все цифры после запятой после n-ой
	return std::trunc(value * pow(10, n)) / pow(10, n);
}

double ePowerMinusXApprox(double& x, double& absError, int& numberMax) {
	const char* PRECISION_NOT_REACHED_EXCEPTION = "Точность не достигнута";
	double result = 1.0;
	double elemI = 1;
	double factorial = 1;
	int factorialMultiply = 2;
	double xPower = -x;
	int nSignsAfterPoint = calcNumbersAfterPoint(absError);

	for (int i = 1; absError < abs(elemI); i++) {
		if (i > numberMax) {
			throw CalculationException {PRECISION_NOT_REACHED_EXCEPTION, truncate(result, nSignsAfterPoint)};
		}
		elemI = xPower / factorial;
		result += elemI;
		xPower *= -x;
		factorial *= factorialMultiply;
		factorialMultiply += 1;
	}
	return truncate(result, nSignsAfterPoint);
}

void printTableLine(
	const double& x, 
	const double& val1, 
	const double& val2, 
	const int& numbersAfterPoint, 
	const int& xFieldWidth, 
	const char& delimiter='|') 
{
	std::cout << delimiter << std::setw(xFieldWidth) << std::setprecision(xFieldWidth-2) << x
		<< delimiter << std::setw(numbersAfterPoint + 2) << std::setprecision(numbersAfterPoint) << val1 
		<< delimiter << std::setw(numbersAfterPoint + 2) << std::setprecision(numbersAfterPoint) << val2
		<< delimiter << std::endl; // +2 для ячеек под первую цифру числа и точку.
}

int main() {
	setlocale(LC_ALL, "RUSSIAN");

	InputException ABSERROR_GENERAL_EXCEPTION = "Абсолютная погрешность";
	InputException NUMBERMAX_GENERAL_EXCEPTION = "Максимальное число слагаемых";
	InputException INTERVAL_GENERAL_EXCEPTION = "Интервал";
	InputException INTERVAL_LIMITS_EXCEPTION = "Интервал (не выполнено условие -1 < x1 <= x2 < 1)";
	InputException INTERVAL_STEP_GENERAL_EXCEPTION = "Шаг интервала";
	
	try {
		std::cout << "Абсолютная погрешность: ";
		double absError = 0.0;
		std::cin >> absError;
		if (!std::cin.good() || absError <= 0) {
			throw ABSERROR_GENERAL_EXCEPTION;
		}
		std::cout << "Максимальное число слагаемых: ";
		int numberMax = 0;
		std::cin >> numberMax;
		if (!std::cin.good() || numberMax <= 0) {
			throw NUMBERMAX_GENERAL_EXCEPTION;
		}
		std::cout << "Интервал (два числа такие, что -1 < x1 <= x2 < 1): ";
		double x1 = 0.0;
		double x2 = 0.0;
		std::cin >> x1 >> x2;
		if (!std::cin.good()) {
			throw INTERVAL_GENERAL_EXCEPTION;
		}
		else if(!(x1 <= x2 && x1 > -1 && x2 < 1)){
			throw INTERVAL_LIMITS_EXCEPTION;
		}

		bool onlyOneIntervalElem = x1 == x2;
		double dx = 2;
		if (!onlyOneIntervalElem) {
			std::cout << "Шаг интервала: ";
			std::cin >> dx;
			if (!std::cin.good() || dx <= 0) {
				throw INTERVAL_STEP_GENERAL_EXCEPTION;
			}
		}
		int numbersAfterPointX1 = calcNumbersAfterPoint(x1);
		int numbersAfterPointX2 = calcNumbersAfterPoint(x2);
		int maxNumbersAfterPointX = (numbersAfterPointX1 > numbersAfterPointX2) ? numbersAfterPointX1 : numbersAfterPointX2;
		
		int numbersAfterPoint = calcNumbersAfterPoint(absError) + MARGIN;
		const int xFieldWidth = maxNumbersAfterPointX + 2; // +2 для вывода "0."
		std::cout << std::endl << DELIMITER << std::setw(xFieldWidth) << "x"
			<< DELIMITER << std::setw(numbersAfterPoint + 2) << "Approx"
			<< DELIMITER << std::setw(numbersAfterPoint + 2) << "exp(-x)"
			<< DELIMITER << std::endl;

		//Меньшевизна эпсилон зависит от количества знаков в пределах интервала
		double epsilon = dx / pow(10, maxNumbersAfterPointX);

		for (double x = x1; x < x2 + epsilon; x += dx) {
			double val1 = 0;
			try {
				val1 = ePowerMinusXApprox(x, absError, numberMax);
			}
			catch (CalculationException exception){
				std::cerr << "Ошибка вычисления: " << exception.what << std::endl;
				val1 = exception.approxValue;
			}
			double val2 = exp(-x);
			printTableLine(x, val1, val2, numbersAfterPoint, xFieldWidth, DELIMITER);
		}
	}
	catch (InputException what) {
		std::cerr << "Ошибка ввода: " << what << std::endl;
		return 1;
	}
	return 0;
}
