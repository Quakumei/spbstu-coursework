#include "Stack.h"
#include <iostream>
#include <utility>

template <typename T>
Stack<T>::Stack() : size_(0),
                    capacity_(1),
                    array_(new T *[capacity_])
{}

template <typename T>
Stack<T>::~Stack()
{
    delete[] array_;
}


template<class U>
void swap(Stack<U>& a, Stack<U>& b) noexcept {
    std::swap(a.array_, b.array_);
    std::swap(a.capacity_, b.capacity_);
    std::swap(a.size_, b.size_);
}

//Конструктор копирования
template <typename T>
Stack<T>::Stack(const Stack<T> &other)
{
    array_ = new T **[other.capacity_];
    capacity_ = other.capacity_;
    size_ = other.size_;
    for (size_t i = 0; i < other.size_; i++)
    {
        *array_[i] = *other.array_[i];
    }
}

// Конструктор перемещения
template <typename T>
Stack<T>::Stack(Stack<T> &&other) noexcept : 
    Stack<T>() //May not work on some machines
{
    swap(*this, other);
}

// Оператор присваивания копированием
template<typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& other) noexcept {
    Stack<T> temp(other);
    swap(*this, temp);
    return *this;
}

// Оператор присваивания перемещением
template<typename T>
Stack<T>& Stack<T>::operator=(Stack<T>&& other) noexcept {
    swap(*this, other);
    return *this;
}

template<typename T>
void Stack<T>::push(T rhs){
    if (capacity_ == size_) {
		capacity_ *= OVERFLOW_MULTIPLIER;
		T** temp = new T * [capacity_];
		for (size_t i = 0; i < size_; i++) {
			temp[i] = array_[i];
		}
		delete[] array_;
		array_ = temp;
	}
	array_[size_] = new T();
	*(array_[size_]) = rhs;
	size_+=1;
}

template <typename T>
T Stack<T>::drop(){
    //Double-check
    if (size_ == 0){
        throw std::logic_error("Empty!");
    }
    --size_;
    return *(array_[size_]);
}

template <typename T>
size_t Stack<T>::getSize(){
    return size_;
}

template <typename T>
void printAll(std::ostream& os, const Stack<T>& container){
    os << "[";
    for (size_t i = 0; i < container.size_; i++)
    {
        os << container.array_[i];
        if (i != container.size_ - 1)
        {
            os << ", ";
        }
    }
    os << "]";
    return;
}