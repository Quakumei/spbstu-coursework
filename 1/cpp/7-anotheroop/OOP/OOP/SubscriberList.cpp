#include "SubscriberList.h"
#include "Subscriber.h"
#include <functional>
#include <iostream>
#include <utility>

#include "comparators.cpp"

SubscriberList::SubscriberList() :
	size_(0),
	capacity_(1),
	array_(new Subscriber* [capacity_])
{ }

SubscriberList::~SubscriberList() {
	for (size_t i = 0; i < size_; i++) {
		delete array_[i];
	}
	delete[] array_;
}


void SubscriberList::sort(std::function<bool(const Subscriber&, const Subscriber&)> compare)
{
	// —ортировка методом выбора
	for (std::size_t i = 0; i < size_ - 1; i++) {
		int min = i;
		for (std::size_t j = i + 1; j < size_; j++) {
			if (compare(*array_[j], *array_[min])) {
				min = j;
			}
		}
		if (min != i) {
			std::swap(array_[i], array_[min]);
		}
	}
}

void SubscriberList::printAll(std::ostream& os) const {
	for (std::size_t i = 0; i < size_; i++) {
		os << *array_[i];
	}
}

void SubscriberList::add(Subscriber s) {
	if (capacity_ == size_) {
		capacity_ *= MULTIPLIER;
		Subscriber** temp = new Subscriber * [capacity_];
		for (std::size_t i = 0; i < size_; i++) {
			temp[i] = array_[i];
		}
		delete[] array_;
		array_ = temp;
	}
	array_[size_] = new Subscriber();
	*(array_[size_]) = s;
	//std::cout << *(array_[size_]) << std::endl;
	++size_;
}

SubscriberList& SubscriberList::operator=(const SubscriberList& sl)
{
	// опируем указатели и работаем с ними.
	this->~SubscriberList();
	size_ = sl.size_;
	capacity_ = sl.capacity_;
	for (size_t i = 0; i < size_; i++) {
		this->array_[i] = sl.array_[i];
	}
	return *this;
}

Subscriber& SubscriberList::operator[](std::size_t pos) const {
	if (0 <= pos && pos < size_) {
		return **(array_ + pos);
	}
	throw std::invalid_argument("Wrong index");
}


SubscriberList::SubscriberList(const SubscriberList& sl) :
	size_(0),
	capacity_(sl.capacity_),
	array_(new Subscriber* [capacity_])
{
	//¬ отличие от оператора присваивани€, создаем новый массив в пам€ти
	for (std::size_t i = 0; i < sl.size_; i++) {
		this->add(sl[i]);
	}
}

int SubscriberList::countUniques() const
{
	SubscriberList temp = *this;
	temp.sort(comparators[COMPARATOR_KEY]);

	//std::clog << "\ndebug: countUniques(): \n";
	//temp.printAll(std::clog);
	//std::clog << "debug end: countUniques()\n";
	//printAll(std::clog);

	int counter = 1;
	for (size_t i = 1; i < size_; i++) {

		if (temp.array_[i]->getName() != temp.array_[i - 1]->getName() ||
			temp.array_[i]->getSurname() != temp.array_[i - 1]->getSurname()) {
			counter++;
			//std::cout << "+";
		}
	}
	return counter;
}

int SubscriberList::countSeverals() const
{
	SubscriberList temp = *this;
	temp.sort(comparators[COMPARATOR_KEY]);

	std::clog << "\ndebug: countUniques(): \n";
	temp.printAll(std::clog);
	std::clog << "debug end: countUniques()\n";

	int counter = 0;
	int phonesCount = 0;
	std::cout << "\n";
	for (size_t i = 1; i < size_; i++) {
		if ((temp.array_[i]->getName() == temp.array_[i - 1]->getName() &&
			temp.array_[i]->getSurname() == temp.array_[i - 1]->getSurname())) {

			if ((temp.array_[i]->getPhone() != temp.array_[i - 1]->getPhone()) &&
				(phonesCount == 1)) {
				counter++;
				phonesCount++;
				//std::cout << "+";
			}
		}
		else {
				phonesCount = 1;
		}
	}
	return counter;
}


