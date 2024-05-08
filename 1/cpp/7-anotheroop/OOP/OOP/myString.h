#pragma once
#include <iostream>

class myString
{
public:
	myString();
	myString(const char* str);
	myString(const myString& s);

	~myString();

	myString& operator=(const myString& other);
	myString operator+(const myString) const;

	void push_back(char c);

	bool empty() const;
	//char* getString() const;
	size_t length() const;

	bool operator>(const myString&) const;
	bool operator<(const myString&) const;
	bool operator==(const myString&) const;
	bool operator!=(const myString&) const;
	bool operator>=(const myString&) const;
	bool operator<=(const myString&) const;

	friend std::ostream& operator<<(std::ostream&, const myString&);
	friend std::istream& operator>>(std::istream&, myString&);

	operator const char* () const;


private:
	static const int CAPACITY_MULTIPLIER_ = 2;
	char* str_;
	std::size_t size_, capacity_;
};
