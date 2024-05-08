#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <functional>
#include <utility>

#include "Subscriber.h"
#include "SubscriberList.h"

typedef std::string string;


int main(){
	setlocale(LC_ALL, "ru-RU");

	try{

		std::ofstream ofs("output.txt");
    	try {
        	ofs.exceptions(ofs.failbit);
    	} catch (const std::ios_base::failure& e)
    	{
       	std::cerr << "Ошибка открытия файла вывода \n"
                  << "Explanatory string: " << e.what() << '\n'
                  << "Error code: " << e.code() << '\n';
    	}
		//Test
		string name = "G.", surname = "Zho-okov" , phone = "+7(960)961-11-11", tariff = "303";
		Subscriber sub = Subscriber(name, surname, phone, tariff);
		std::cout << "TestSub\t: " << sub << '\n';


		std::cout << "Введите имя тест-файла\n>>";
		string filename = "1.txt";
		std::cin >> filename;
		
		std::ifstream ifs(filename);
    	try {
        	ifs.exceptions(ifs.failbit);
    	} catch (const std::ios_base::failure& e)
    	{
       	std::cerr << "Ошибка открытия файла ввода \n"
                  << "Explanatory string: " << e.what() << '\n'
                  << "Error code: " << e.code() << '\n';
    	}

    	int n = 0;
    	ifs >> n;
    	if (n <= 0){
    		throw std::invalid_argument( "array size must be greater than 0" );
    	}

    	SubscriberList subList;
    	for (int i = 0; i < n; i++){
    		Subscriber tempSub;
    		ifs >> tempSub;
    		std::cout << "Entering: " << tempSub << '\n';
			subList.add(tempSub);
			subList.printAll(std::cout); 
    	}

    	std::cout << "---- Введённый массив ----\n";
    	subList.printAll(std::cout);


    	// Sort
    	std::function<bool(const Subscriber&, const Subscriber&)> compareNames = [](const Subscriber& a, const Subscriber& b)->bool{return a.getName() < b.getName();};
    	std::function<bool(const Subscriber&, const Subscriber&)> compareSurnames = [](const Subscriber& a, const Subscriber& b)->bool{return a.getSurname() < b.getSurname();};
    	std::function<bool(const Subscriber&, const Subscriber&)> compareTariffs = [](const Subscriber& a, const Subscriber& b)->bool{return a.getTariff() < b.getTariff();};
    	std::function<bool(const Subscriber&, const Subscriber&)> comparePhones = [](const Subscriber& a, const Subscriber& b)->bool{return a.getPhone() < b.getPhone();};

    	std::cout << '\n' << "Выберите столбец сортировки:\n1-Фамилия\n2-Имя\n3-Тариф\n4-НомерТелефона\n>>";
    	int choice = 0;
    	std::cin >> choice;
    	switch(choice){
    		case 1:
    		subList.sort(compareSurnames);
    		break;
    		case 2:
    		subList.sort(compareNames);
    		break;
    		case 3:
    		subList.sort(compareTariffs);
    		break;
    		case 4:
    		subList.sort(comparePhones);
    		break;
    		default:
    		throw std::invalid_argument( "you should choose a number between 1 and 4" );
    	}

    	ofs << "Отсортированный массив:\n";
    	ofs << n << '\n';
    	subList.printAll(ofs);
    	subList.printAll(std::cout);

    	// Count uniques
    	int uniqueCounter = 1;
    	int severalPhonesCount = 0;
    	int phones = 0;
    	for(int i = 1; i < n; i++){
    		if (subList[i].getName() != subList[i-1].getName() || subList[i].getSurname() != subList[i-1].getSurname()){
    			phones = 0;
    			uniqueCounter++;
    		}
    		phones++;
    		if (phones == 2){
    			severalPhonesCount += 1;
    		}
    	}

    	ofs << "\nUnique count: " << uniqueCounter << '\n';
    	ofs << "Many numbers owners: " << severalPhonesCount << '\n';



	} catch (const std::invalid_argument& e){
		std::cerr << "invalid_argument: " << e.what() << '\n';
	}
	return 0;
}
