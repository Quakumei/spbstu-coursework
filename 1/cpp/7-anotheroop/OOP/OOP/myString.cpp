#include "myString.h"
#include <cstdlib>


myString::myString()
{
	str_ = new char[1];
	*str_ = 0;
	size_ = 0;
	capacity_ = 1;
}

myString::myString(const char* str)
{
	std::size_t temp = 0;
	for (temp; str[temp] != '\0'; temp++) {}
	temp++;
	str_ = new char[temp];
	for (std::size_t i = 0; i < temp; ++i)
		*(str_ + i) = *(str + i);
	size_ = temp-1;
	capacity_ = temp;
}

myString::myString(const myString& s) {
	size_ = s.size_;
	capacity_ = s.capacity_;
	str_ = new char[capacity_];
	for (std::size_t i = 0; i < size_+1; ++i)
	{
		*(str_ + i) = *(s.str_ + i);
	}		
}

myString& myString::operator=(const myString& s)
{
	this->~myString();
	size_ = s.size_;
	capacity_ = s.capacity_;
	str_ = new char[capacity_];
	for (std::size_t i = 0; i < capacity_; ++i)
	{
		*(str_ + i) = *(s.str_ + i);
	}
	return *this;
}

myString myString::operator+(const myString rhs) const
{
	//std::cout << '\n' << *this << " + " << rhs << " = ";
	myString temp = *this;
	//std::cout << "( " << rhs.size_ << ' ' << size_ << "temp:" << temp << " )";
	for (size_t i = 0; i < rhs.size_; i++) {
		temp.push_back(rhs[i]);
	}
	return myString(temp);
}

myString::~myString()
{
	delete[] str_;
}

bool myString::empty() const
{ 
	return !size_; 
}

//char* myString::getString() const
//{
//	return str_;
//}

size_t myString::length() const 
{ 
	return size_; 
}

void myString::push_back(char c)
{
	if (size_ == capacity_ - 1)
	{
		capacity_ *= CAPACITY_MULTIPLIER_;
		char* temp = new char[capacity_];
		std::memcpy(temp, str_, size_+1);
		delete[] str_;
		str_ = temp;
	}
	str_[size_] = c;
	size_++;
	str_[size_] = 0;
}

bool myString::operator<(const myString& s) const
{
	const myString& s1 = *this;
	const myString& s2 = s;
	size_t temp = (s1.size_ < s2.size_) ? s1.size_ : s2.size_;
	
	for (size_t i = 0; i < temp; ++i)
	{
		if (s1.str_[i] < s2.str_[i]) 
		{
			return true;
		}
		else if (s1.str_[i] > s2.str_[i]) 
		{
			return false;
		}
	}
	if (s1.size_ == s2.size_)
		return false;
	else if (temp == s1.size_)
		return true;
	return false;
}



bool myString::operator==(const myString& s) const
{
	const myString& s1 = *this;
	const myString& s2 = s;
	size_t temp = (s1.size_ < s2.size_) ? s1.size_ : s2.size_;
	for (size_t i = 0; i < temp; ++i)
	{
		if (s1.str_[i] != s2.str_[i])
		{
			return false;
		}
	}
	return true;
}

bool myString::operator!=(const myString& s) const {
	return !(*this == s);
}

bool myString::operator>(const myString& s) const
{
	const myString& s1 = *this;
	const myString& s2 = s;
	return (s1 != s2) && !(s1 < s2);
}

bool myString::operator>=(const myString& s) const
{
	return (*this > s) || (*this == s);
}

bool myString::operator<=(const myString& s) const
{
	return (*this < s) || (*this == s);
}




std::ostream& operator<<(std::ostream& os, const myString& s)
{
	os << s.str_;
	return os;
}

std::istream& operator>>(std::istream& is, myString& s)
{
	char c = 0;
	delete[] s.str_;

	s.str_ = new char[1];
	*s.str_ = 0;
	s.capacity_ = 1;
	s.size_ = 0;

	c = is.peek();
	while (c == ' ' || c == '\n' || c == '\t' || c == '\r')
	{
		is.get(c);
		c = is.peek();
	}
	is.get(c);
	while (!(c == ' ' || c == '\n' || c == '\t' || c == '\r'))
	{
		s.push_back(c);
		is.get(c);
		if (is.eof()) break;
	}
	return is;
}


myString::operator const char* () const {
	return this->str_;
}