#ifndef STACK_H
#define STACK_H

#include "List.hpp"
template <class T>
class Stack : public List<T>
{
public:
    Stack(){};
    ~Stack(){};

    // реализуем интерфейс
    void push(T d) { list_.pushBack(d); };
    T drop() { return list_.dropFront(); };
    T peek() const { return list_.top(); };
    bool isEmpty() const { return list_.isEmpty(); }

private:
    List<T> list_;
};
#endif
