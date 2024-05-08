#include "SubscriberList.h"
#include "Subscriber.h"
#include <functional>
#include <iostream>
#include <utility>

SubscriberList::SubscriberList() :
	size_(0),
	capacity_(1),
	array_(new Subscriber*[capacity_])
	{}
SubscriberList::~SubscriberList(){
	delete[] array_;
}


void SubscriberList::sort(std::function<bool(const Subscriber&, const Subscriber&)> compare)
{
	// Сортировка методом выбора
    for (int i = 0; i < size_-1; i++){
    	int min = i;
    	for (int j = i+1; j < size_; j++ ){
    		if (compare(*array_[j], *array_[min])){
    			min = j;
    		}
    	}
    	if (min != i){
    		std::swap(array_[i], array_[min]);
    	}
    }
}

void SubscriberList::printAll(std::ostream& os) const{
	for(int i = 0; i < size_ ; i++){
		os << *array_[i];
	}
}

void SubscriberList::add(Subscriber s) {
		if (capacity_ == size_){
			capacity_ *= MULTIPLIER;
			Subscriber** temp = new Subscriber*[capacity_];
			for(int i = 0; i < size_; i++){
				 temp[i] = array_[i];
			}
			delete[] array_;
			array_ = temp;
		}
		*array_[size_] = s;
		++size_;
}

Subscriber& SubscriberList::operator[](std::size_t pos) const {
    if (0 <= pos && pos < size_) {
        return **(array_ + pos);
    }
    throw std::invalid_argument("Wrong index");
}

