#ifndef STRING_H
#define STRING_H

#include <iostream>
#include <cstddef>
#include <cstring>

class String {
public:
	//TODO: Перенести реализаци. в String.cpp
	String(): //Список инициализации
		size_(0),
		capacity_(1),
		pointer_(new char[1]),
	{
		pointer_[0] = '\0';
	}

	String(const char * s):
		size_(std::strlen(s)),
		capacity_(size_+1),
		pointer_(new char[capacity_])
	{
		strcpy_s(this->pointer_, capacity_, s);
	}

	String(const String& str):
		size_(str.size_),
		capacity_(str.capacity_),
		pointer_(new char[capacity_])
	{
		strcpy_s(this->pointer_, capacity_, str.pointer_);
	}

		// pointer_ = new char[1];
		// pointer_[0] = '\0';
		// capacity_ = 1;
		// size_ = 0;
	std::size_t getSize() const{
		return size_;
	}

	~String(){
		delete[] pointer_;
	}

	friend std::ostream& operator<<(std::ostream& os, const String& str);


private:
	std::size_t capacity_;
	std::size_t size_;
	char* pointer_; 
};

#endif