#pragma once
#include <iostream>
#include <functional>
#include "Subscriber.h"

class SubscriberList {
public:
	SubscriberList();
	SubscriberList(const SubscriberList&);
	SubscriberList& operator=(const SubscriberList&);
	~SubscriberList();

	void add(Subscriber s);
	void sort(std::function<bool(const Subscriber&, const Subscriber&)> compare);
	void printAll(std::ostream&) const;

	
	Subscriber& operator[](std::size_t pos) const;
	
	int countUniques() const;
	int countSeverals() const;


private:
	static const int MULTIPLIER = 2;
	std::size_t size_;
	int capacity_;
	Subscriber** array_;
};


