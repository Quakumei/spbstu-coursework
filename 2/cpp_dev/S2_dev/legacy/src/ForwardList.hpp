#ifndef LIST_H
#define LIST_H

#include <iostream>

#include "ForwardListIterator.hpp"

namespace tampio
{
  template< class T >
  class ForwardList
  {
  private:
    struct node_t;

  public:
    using ValueType = T;
    using StructType = node_t;
    using Iterator = ForwardListIterator< ForwardList< T > >;

  public:
    ForwardList();
    ~ForwardList();
    ForwardList(const ForwardList &);
    ForwardList(ForwardList &&) noexcept;
    ForwardList &operator=(const ForwardList &);
    ForwardList &operator=(ForwardList &&) noexcept;

    Iterator begin() const;
    Iterator beforeBegin() const;
    Iterator end() const;

    void pushTail(const T &);
    void pushHead(const T &);

    // По аналогии с std::vector
    void rmFront();
    T top() const;
    T bottom() const;
    bool isEmpty() const noexcept;

  private:
    struct node_t
    {
      T data;
      node_t *next;
    };

    void swap(ForwardList &) noexcept;

    node_t *head_;
    node_t *tail_;
  };
}

template< class T >
void tampio::ForwardList< T >::rmFront()
{
  if (!head_)
  {
    throw std::logic_error("List is empty");
  }
  node_t *temp = head_;
  head_ = (head_ == tail_) ? tail_ = nullptr : head_->next;
  delete temp;
}
template< class T >
T tampio::ForwardList< T >::top() const
{
  return head_->data;
}

template< class T >
void tampio::ForwardList< T >::pushTail(const T &d)
{
  if (!head_)
  {
    head_ = tail_ = new node_t;
  }
  else
  {
    tail_->next = new node_t;
    tail_ = tail_->next;
  }
  tail_->data = d;
  tail_->next = nullptr;
}
template< class T >
void tampio::ForwardList< T >::pushHead(const T &val)
{
  node_t *newNode = new node_t;
  newNode->data = val;
  newNode->next = head_;
  head_ = newNode;
}

template< class T >
T tampio::ForwardList< T >::bottom() const
{
  return tail_->data;
}

template< class T >
tampio::ForwardList< T >::ForwardList() :
    head_(nullptr),
    tail_(nullptr)
{}

template< class T >
tampio::ForwardList< T >::ForwardList(const ForwardList &list) :
    head_(nullptr),
    tail_(nullptr)
{
  tampio::ForwardList< T > temp;
  node_t *src = list.head_;
  while (src)
  {
    temp.pushTail(src->data);
    src = src->next;
  }
  swap(temp);
}

template< class T >
tampio::ForwardList< T >::ForwardList(ForwardList &&list) noexcept :
    head_(nullptr),
    tail_(nullptr)
{
  swap(list);
}

template< class T >
tampio::ForwardList< T >::~ForwardList()
{
  while (head_)
  {
    node_t *temp = head_;
    head_ = head_->next;
    delete temp;
  }
}

template< class T >
tampio::ForwardList< T > &tampio::ForwardList< T >::operator=(const ForwardList &list)
{
  if (this == &list)
  {
    return *this;
  }

  tampio::ForwardList< T > tempList(list);
  swap(tempList);

  return *this;
}

template< class T >
tampio::ForwardList< T > &tampio::ForwardList< T >::operator=(ForwardList &&list) noexcept
{
  swap(list);
  return *this;
}

template< class T >
bool tampio::ForwardList< T >::isEmpty() const noexcept
{
  return !head_;
}

template< class T >
void tampio::ForwardList< T >::swap(ForwardList &list) noexcept
{
  std::swap(head_, list.head_);
  std::swap(tail_, list.tail_);
}

// Iterator patch
template< class T >
using ForwardList = tampio::ForwardList< T >;

template< class T >
typename tampio::ForwardList< T >::Iterator tampio::ForwardList< T >::begin() const
{
  return tampio::ForwardList< T >::Iterator(head_);
}

template< class T >
typename tampio::ForwardList< T >::Iterator tampio::ForwardList< T >::beforeBegin() const
{
  // Untested
  typename tampio::ForwardList< T >::Iterator it(head_);
  it->data_ = nullptr;
  it->next_ = head_;
  return it;
}

template< class T >
typename tampio::ForwardList< T >::Iterator tampio::ForwardList< T >::end() const
{
  return tampio::ForwardList< T >::Iterator(tail_);
}

#endif
