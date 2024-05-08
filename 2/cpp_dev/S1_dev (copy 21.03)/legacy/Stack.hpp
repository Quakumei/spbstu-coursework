#ifndef STACK_H
#define STACK_H

#include "List.hpp"

template <class T>
class Stack : List
{
public:
    Stack();
    ~Stack();

    //  Реализуем методы
    void push(T);
    T drop();

    void print(std::ostream &) const;
    std::string print() const;
    T peek() const;
    bool isEmpty() const;

private:
    struct node_t
    {
        T data;
        node_t *next;
    };

    node_t *head_;

    Stack<T>(const Stack<T> &) = delete;
    Stack<T>(Stack<T> &&) = delete;
    Stack<T> &operator=(const Stack<T> &) = delete;
    Stack<T> &operator=(Stack<T> &&) = delete;
};

template <class T>
bool Stack<T>::isEmpty() const
{
    return !head_;
}

template <class T>
Stack<T>::Stack() : head_(nullptr)
{
}

template <class T>
Stack<T>::~Stack()
{
    while (head_)
    {
        node_t *temp = head_;
        head_ = head_->next;

        delete temp;
    }
}

template <class T>
void Stack<T>::push(T val)
{
    node_t *newNode = new node_t;
    newNode->data = val;
    newNode->next = head_;
    head_ = newNode;
}

template <class T>
T Stack<T>::drop()
{
    if (!head_)
    {
        throw std::logic_error("Stack is empty");
    }
    T res = head_->data;
    node_t *temp = head_;
    head_ = head_->next;
    delete temp;
    return res;
}

template <class T>
void Stack<T>::print(std::ostream &stream) const
{
    node_t *temp = head_;
    stream << "[ ";
    while (temp)
    {
        stream << temp->data << "  ";
        temp = temp->next;
    }
    stream << "]";
}

template <class T>
std::string Stack<T>::print() const
{
    std::string res = "[ ";
    node_t *temp = head_;
    while (temp)
    {
        res.append("" + temp->data);
        res.append(" ");
        temp = temp->next;
    }
    res.append("]");
    return res;
}

template <class T>
T Stack<T>::peek() const
{
    return head_->data;
}
#endif
