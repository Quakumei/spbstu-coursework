#ifndef QUEUE_H
#define QUEUE_H

#include "List.hpp"
template <class T>
class Queue : public List<T>
{
public:
    Queue(){};
    ~Queue(){};

    // реализуем интерфейс
    void push(T d) { list_.pushFront(d); };
    T drop() { return list_.dropFront(); };
    T peek() const { return list_.top(); };
    bool isEmpty() const { return list_.isEmpty(); }

private:
    List<T> list_;
};
#endif
