#ifndef STACK_H
#define STACK_H

#include "List.hpp"
namespace tampio
{
    template < class T >
    class Stack
    {
    public:
        Stack< T >() = default;
        ~Stack< T >() = default;

        void push(const T &a);

        void rm_back();
        T peek() const;

        bool isEmpty() const;

    private:
        List< T > list_;
    };

}
template < class T >
void tampio::Stack< T >::push(const T &a)
{
    list_.pushHead(a);
}
template < class T >
void tampio::Stack< T >::rm_back()
{
    list_.rm_back();
}
template < class T >
T tampio::Stack< T >::peek() const
{
    return list_.top();
}
template < class T >
bool tampio::Stack< T >::isEmpty() const
{
    return list_.isEmpty();
}

#endif
