#pragma once
#include <string>
#include <iostream>
#include "myString.h"

typedef std::string string;
//typedef myString string;


class Subscriber {
public:

	Subscriber(string&, string&, string&, string&);
	Subscriber();
	Subscriber(const Subscriber& src);

	const string& getName() const;
	const string& getSurname() const;
	const string& getPhone() const;
	const string& getTariff() const;

	void setName(const string& value);
	void setSurname(const string& value);
	void setPhone(const string& value);
	void setTariff(const string& value);

	friend std::istream& operator>>(std::istream& is, Subscriber& sub);
	friend std::ostream& operator<<(std::ostream& os, const Subscriber& sub);



private:
	string name_;
	string surname_;
	string phone_;
	string tariff_;
};

