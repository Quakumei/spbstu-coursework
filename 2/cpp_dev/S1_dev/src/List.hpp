#ifndef LIST_H
#define LIST_H

#include <iostream>
namespace tampio
{
  template < class T >
  class List
  {
  public:
    List();
    ~List();
    List(const List &);
    List(List &&) noexcept;
    List &operator=(const List &);
    List &operator=(List &&) noexcept;

    void pushTail(const T &);
    void pushHead(const T &);

    T dropHead();

    // По аналогии с std::vector
    void rm_back();
    T top() const;
    T bottom() const;

    bool isEmpty() const noexcept;

  private:
    struct node_t
    {
      T data;
      node_t *next;
    };

    void swap(List &) noexcept;

    node_t *head_;
    node_t *tail_;
  };
}

template < class T >
void tampio::List< T >::rm_back()
{
  if (!head_)
  {
    throw std::logic_error("List is empty");
  }
  node_t *temp = head_;
  head_ = (head_ == tail_) ? tail_ = nullptr : head_->next;
  delete temp;
}
template < class T >
T tampio::List< T >::top() const
{
  return head_->data;
}
template < class T >
T tampio::List< T >::dropHead()
{
  if (!head_)
  {
    throw std::logic_error("List is empty");
  }
  T res = head_->data;
  node_t *temp = head_;
  head_ = (head_ == tail_) ? tail_ = nullptr : head_->next;
  delete temp;
  return res;
}

template < class T >
void tampio::List< T >::pushTail(const T &d)
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
template < class T >
void tampio::List< T >::pushHead(const T &val)
{
  node_t *newNode = new node_t;
  newNode->data = val;
  newNode->next = head_;
  head_ = newNode;
}

template < class T >
T tampio::List< T >::bottom() const
{
  return tail_->data;
}

template < class T >
tampio::List< T >::List() : head_(nullptr), tail_(nullptr)
{
}

template < class T >
tampio::List< T >::List(const List &list) : head_(nullptr), tail_(nullptr)
{
  tampio::List< T > temp;
  node_t *src = list.head_;
  while (src)
  {
    temp.pushTail(src->data);
    src = src->next;
  }
  swap(temp);
}

template < class T >
tampio::List< T >::List(List &&list) noexcept : head_(nullptr), tail_(nullptr)
{
  swap(list);
}

template < class T >
tampio::List< T >::~List()
{
  while (head_)
  {
    node_t *temp = head_;
    head_ = head_->next;
    delete temp;
  }
}

template < class T >
tampio::List< T > &tampio::List< T >::operator=(const List &list)
{
  if (this == &list)
  {
    return *this;
  }

  tampio::List< T > tempList(list);
  swap(tempList);

  return *this;
}

template < class T >
tampio::List< T > &tampio::List< T >::operator=(List &&list) noexcept
{
  swap(list);
  return *this;
}

template < class T >
bool tampio::List< T >::isEmpty() const noexcept
{
  return !head_;
}

template < class T >
void tampio::List< T >::swap(List &list) noexcept
{
  std::swap(head_, list.head_);
  std::swap(tail_, list.tail_);
}
#endif
