#include "Subscriber.h"
#include <iostream>
#include <cctype>
#include <stdexcept>


string const& Subscriber::getName() const {
	return name_;
}

string const& Subscriber::getSurname() const {
	return surname_;
}

string const& Subscriber::getPhone() const {
	return phone_;
}

string const& Subscriber::getTariff() const {
	return tariff_;
}

inline bool isName(const string& s) {
	return std::isupper(s[0]) && s[1] == '.';
}

void Subscriber::setName(const string& value) {
	if (!(
		value.length() == 2 &&
		isName(value)))
	{
		throw std::invalid_argument("Имя должно быть заглавной буквой с точкой.");
	}
	this->name_ = value;
}

inline bool isWordDashed(const string& s) {
	for (int i = 0; s[i] != '\0'; i++) {
		if (!(std::isalpha(s[i]) || (s[i] == '-' && i != 0 && i != s.length() - 1))) {
			return false;
		}
	}
	return true;
}

void Subscriber::setSurname(const string& value) {
	if (!(
		value.length() >= 3 &&
		value.length() <= 20 &&
		std::isupper(value[0]) &&
		isWordDashed(value)))
	{
		throw std::invalid_argument("Фамилия должна начинаться с большой буквы и быть словом");
	}
	this->surname_ = value;
}

inline bool isPhone(const string& s) {
	//+x(xxx)xxx-xx-xx
	for (int i = 0; s[i] != '\0'; i++) {
		if (!(
			(std::isdigit(s[i]) && i != 0 && i != 2 && i != 6 && i != 10 && i != 13) ||
			(s[i] == '+' && i == 0) ||
			(s[i] == '-' && (i == 13 || i == 10)) ||
			(s[i] == '(' && i == 2) ||
			(s[i] == ')' && i == 6)
			))
		{
			std::cout << "i:\t" << i << "--> '" << s[i] << "'\n";
			return false;
		}
	}
	return true;
}

void Subscriber::setPhone(const string& value) {
	if (!(
		value.length() == 16 &&
		isPhone(value)
		))
	{
		throw std::invalid_argument("Телефон должен быть записан в форме +x(xxx)xxx-xx-xx");
	}
	this->phone_ = value;
}

inline bool isTariff(const string& s) {
	for (int i = 0; s[i] != '\0'; i++) {
		if (!std::isdigit(s[i])) {
			return false;
		}
	}
	return true;
}

void Subscriber::setTariff(const string& value) {
	if (!(
		value.length() == 3 &&
		isTariff(value)
		))
	{
		throw std::invalid_argument("Тариф должен состоять из трёх цифр");
	}
	this->tariff_ = value;
}



Subscriber::Subscriber(string& name, string& surname, string& phone, string& tariff) {
	this->setName(name);
	this->setSurname(surname);
	this->setPhone(phone);
	this->setTariff(tariff);
}

Subscriber::Subscriber() {
	name_ = "X.";
	surname_ = "X-XXXXXXXXXXXXXXXXXX";
	phone_ = "+X(XXX)XXX-XX-XX";
	tariff_ = "XXX";
}

std::istream& operator>>(std::istream& is, Subscriber& sub) {
	string name = "", surname = "", phone = "", tariff = "";
	is >> surname >> name >> phone >> tariff;
	sub = Subscriber(name, surname, phone, tariff);
	return is;
}

std::ostream& operator<<(std::ostream& os, const Subscriber& sub) {
	os << "[ " << sub.getName() << ", " << sub.getSurname() << ", " << sub.getPhone() << ", " << sub.getTariff() << " ]\n";
	return os;
}

Subscriber::Subscriber(const Subscriber& src) {
	name_ = src.name_;
	surname_ = src.surname_;
	phone_ = src.phone_;
	tariff_ = src.tariff_;
}
