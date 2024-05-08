#ifndef QUEUE_H
#define QUEUE_H

#include "List.hpp"
namespace tampio
{
    template < class T >
    class Queue
    {
    public:
        Queue< T >() = default;
        ~Queue< T >() = default;

        void push(const T &a);

        T peek() const;
        void rm_back();

        bool isEmpty() const;

    private:
        List< T > list_;
    };
}

template < class T >
void tampio::Queue< T >::push(const T &a)
{
    list_.pushTail(a);
}
template < class T >
void tampio::Queue< T >::rm_back()
{
    list_.rm_back();
}
template < class T >
T tampio::Queue< T >::peek() const
{
    return list_.top();
}
template < class T >
bool tampio::Queue< T >::isEmpty() const
{
    return list_.isEmpty();
}

#endif
