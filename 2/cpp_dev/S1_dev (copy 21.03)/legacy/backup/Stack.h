#ifndef STACK_H
#define STACK_H

#include <iostream>



template<class T>
class Stack{
    public:
        //Конструктор
        Stack();

        // Деструктор
        ~Stack();

        // Конструктор копирования
        // Создать копию объекта
        Stack(const Stack<T>& other);

        // Конструктор перемещения
        // Взять данные
        Stack(Stack<T>&& other) noexcept;

        // Оператор присваивания копированием
        Stack<T>& operator=(const Stack<T>& other) noexcept;

        // Оператор присваивания перемещением
        Stack<T>& operator=(Stack<T>&& other) noexcept;

        template <class U>
        friend void swap(Stack<U>&, Stack<U>&) noexcept;

        void push(T rhs);
        T drop();

        size_t getSize();
    private: 
        static const int OVERFLOW_MULTIPLIER = 2;
        T** array_;
        size_t size_;
        size_t capacity_;

};
#endif