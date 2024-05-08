#ifndef BIDIRECTIONAL_LIST_HPP
#define BIDIRECTIONAL_LIST_HPP

#include <ostream>
#include <stdexcept>
#include <utility>

namespace tampio
{
  template< class T >
  class BidirectionalList
  {
  public:
    BidirectionalList();
    BidirectionalList(const BidirectionalList &);
    BidirectionalList(BidirectionalList &&) noexcept;
    ~BidirectionalList();
    BidirectionalList &operator=(const BidirectionalList &);
    BidirectionalList &operator=(BidirectionalList &&) noexcept;

    void pushBack(const T &);
    void pushFront(const T &);
    void deleteFront();
    void deleteBack();
    T front() const;
    T tail() const;
    bool empty() const noexcept;

    class Iterator;
    Iterator begin();
    Iterator end();
    const Iterator begin() const;
    const Iterator end() const;
    Iterator beforeEnd();
    const Iterator beforeEnd() const;
    void print(std::ostream &) const;
    const Iterator insertBefore(const Iterator &, const T &);
    void deleteNode(const Iterator &);

  private:
    struct node_t
    {
      T data;
      node_t *next;
      node_t *previous;
    };

    void swap(BidirectionalList &) noexcept;

    node_t *head_;
    node_t *tail_;
  };

  template< class T >
  class BidirectionalList< T >::Iterator
  {
  public:
    Iterator();
    Iterator(node_t *);
    Iterator(const Iterator &);
    ~Iterator() = default;
    Iterator &operator=(const Iterator &);
    T &operator*();
    const T &operator*() const;
    T *operator->();
    const T *operator->() const;
    bool operator!=(const Iterator &) const;
    bool operator==(const Iterator &) const;
    Iterator &operator++();
    Iterator operator++(int);
    Iterator &operator--();
    Iterator operator--(int);
    Iterator operator+(int);

  private:
    node_t *nodeptr_;
    node_t *nextptr_;
    friend BidirectionalList;
  };
}
template< class T >
void tampio::BidirectionalList< T >::deleteFront()
{
  if (empty())
  {
    throw std::logic_error("BidirectionalList is empty");
  }
  node_t *temp = head_;
  head_ = (head_ == tail_) ? tail_ = nullptr : head_->next;
  if (head_)
  {
    head_->previous = nullptr;
  }
  delete temp;
}
template< class T >
void tampio::BidirectionalList< T >::deleteBack()
{
  if (empty())
  {
    throw std::logic_error("BidirectionalList is empty");
  }
  node_t *temp = tail_;
  tail_ = (head_ == tail_) ? head_ = nullptr : tail_->previous;
  if (tail_)
  {
    tail_->next = nullptr;
  }
  delete temp;
}
template< class T >
T tampio::BidirectionalList< T >::front() const
{
  return head_->data;
}
template< class T >
void tampio::BidirectionalList< T >::pushBack(const T &item)
{
  node_t *former_tail = tail_;
  if (empty())
  {
    head_ = tail_ = new node_t;
  }
  else
  {
    tail_->next = new node_t;
    tail_ = tail_->next;
  }
  tail_->data = item;
  tail_->next = nullptr;
  tail_->previous = former_tail;
}
template< class T >
void tampio::BidirectionalList< T >::pushFront(const T &val)
{
  node_t *newNode = new node_t;
  newNode->data = val;
  newNode->next = head_;
  newNode->previous = nullptr;
  if (empty())
  {
    tail_ = head_ = newNode;
  }
  else
  {
    head_ = newNode;
    head_->next->previous = head_;
  }
}
template< class T >
T tampio::BidirectionalList< T >::tail() const
{
  return tail_->data;
}
template< class T >
tampio::BidirectionalList< T >::BidirectionalList() :
    head_(nullptr),
    tail_(nullptr)
{
}
template< class T >
tampio::BidirectionalList< T >::BidirectionalList(const BidirectionalList &biList) :
    head_(nullptr),
    tail_(nullptr)
{
  tampio::BidirectionalList< T > temp;
  node_t *src = biList.head_;
  while (src)
  {
    temp.pushBack(src->data);
    src = src->next;
  }
  swap(temp);
}
template< class T >
tampio::BidirectionalList< T >::BidirectionalList(BidirectionalList &&forwardList) noexcept :
    head_(nullptr),
    tail_(nullptr)
{
  swap(forwardList);
}
template< class T >
tampio::BidirectionalList< T >::~BidirectionalList()
{
  while (head_)
  {
    node_t *temp = head_;
    head_ = head_->next;
    delete temp;
  }
}
template< class T >
tampio::BidirectionalList< T > &tampio::BidirectionalList< T >::operator=(const BidirectionalList &biList)
{
  if (this == &biList)
  {
    return *this;
  }
  tampio::BidirectionalList< T > tempBidirectionalList(biList);
  swap(tempBidirectionalList);
  return *this;
}
template< class T >
tampio::BidirectionalList< T > &tampio::BidirectionalList< T >::operator=(BidirectionalList &&forwardList) noexcept
{
  swap(forwardList);
  return *this;
}
template< class T >
bool tampio::BidirectionalList< T >::empty() const noexcept
{
  return !head_;
}
template< class T >
void tampio::BidirectionalList< T >::swap(BidirectionalList &forwardList) noexcept
{
  std::swap(head_, forwardList.head_);
  std::swap(tail_, forwardList.tail_);
}

template< class T >
tampio::BidirectionalList< T >::Iterator::Iterator() :
    nodeptr_(nullptr),
    nextptr_(nullptr){};
template< class T >
tampio::BidirectionalList< T >::Iterator::Iterator(const Iterator &other) :
    nodeptr_(other.nodeptr_),
    nextptr_(other.nextptr_){};
template< class T >
tampio::BidirectionalList< T >::Iterator::Iterator(node_t *node)
{
  nodeptr_ = node;
  nextptr_ = (node) ? node->next : nullptr;
};

template< class T >
typename tampio::BidirectionalList< T >::Iterator &tampio::BidirectionalList< T >::Iterator::operator=(
    const Iterator &other)
{
  nodeptr_ = other.nodeptr_;
  nextptr_ = other.nextptr_;
  return *this;
}

template< class T >
T &tampio::BidirectionalList< T >::Iterator::operator*()
{
  return nodeptr_->data;
}
template< class T >
const T &tampio::BidirectionalList< T >::Iterator::operator*() const
{
  return nodeptr_->data;
}
template< class T >
T *tampio::BidirectionalList< T >::Iterator::operator->()
{
  return &(nodeptr_->data);
}
template< class T >
const T *tampio::BidirectionalList< T >::Iterator::operator->() const
{
  return &(nodeptr_->data);
}
template< class T >
bool tampio::BidirectionalList< T >::Iterator::operator==(const Iterator &oth) const
{
  return nodeptr_ == oth.nodeptr_ && nextptr_ == oth.nextptr_;
}
template< class T >
bool tampio::BidirectionalList< T >::Iterator::operator!=(const Iterator &oth) const
{
  return !(nodeptr_ == oth.nodeptr_);
}
template< class T >
typename tampio::BidirectionalList< T >::Iterator &tampio::BidirectionalList< T >::Iterator::operator++()
{
  nodeptr_ = nextptr_;
  if (nodeptr_ != nullptr)
  {
    nextptr_ = nodeptr_->next;
  }
  else
  {
    nextptr_ = nullptr;
  }
  return *this;
}
template< class T >
typename tampio::BidirectionalList< T >::Iterator &tampio::BidirectionalList< T >::Iterator::operator--()
{
  nodeptr_ = nodeptr_->previous;
  if (nodeptr_ != nullptr)
  {
    nextptr_ = nodeptr_->next;
  }
  else
  {
    nextptr_ = nullptr;
  }
  return *this;
}
template< class T >
typename tampio::BidirectionalList< T >::Iterator tampio::BidirectionalList< T >::Iterator::operator++(int)
{
  Iterator temp(nodeptr_);
  ++(*this);
  return temp;
}
template< class T >
typename tampio::BidirectionalList< T >::Iterator tampio::BidirectionalList< T >::Iterator::operator--(int)
{
  Iterator temp(nodeptr_);
  --(*this);
  return temp;
}
template< class T >
typename tampio::BidirectionalList< T >::Iterator tampio::BidirectionalList< T >::Iterator::operator+(int n)
{
  if (n == 0)
  {
    return *this;
  }
  else if (n < 0)
  {
    throw std::logic_error("traversing back via number isn't implemented, use operator-- instead");
  }
  node_t *setnode;
  if (nodeptr_)
  {
    setnode = nodeptr_;
  }
  else
  {
    setnode = nextptr_;
    n--;
  }
  Iterator temp(setnode);
  while (n != 0)
  {
    temp++;
    n--;
  }
  return temp;
}

template< class T >
typename tampio::BidirectionalList< T >::Iterator tampio::BidirectionalList< T >::begin()
{
  return Iterator(head_);
}
template< class T >
typename tampio::BidirectionalList< T >::Iterator tampio::BidirectionalList< T >::end()
{
  return Iterator();
}
template< class T >
typename tampio::BidirectionalList< T >::Iterator tampio::BidirectionalList< T >::beforeEnd()
{
  return Iterator(tail_);
}

template< class T >
const typename tampio::BidirectionalList< T >::Iterator tampio::BidirectionalList< T >::begin() const
{
  return Iterator(head_);
}
template< class T >
const typename tampio::BidirectionalList< T >::Iterator tampio::BidirectionalList< T >::end() const
{
  return Iterator();
}
template< class T >
const typename tampio::BidirectionalList< T >::Iterator tampio::BidirectionalList< T >::beforeEnd() const
{
  return Iterator(tail_);
}

template< class T >
const typename tampio::BidirectionalList< T >::Iterator
tampio::BidirectionalList< T >::insertBefore(const Iterator &pos, const T &item)
{
  if (pos == begin())
  {
    pushFront(item);
    return begin();
  }
  else if (pos == end())
  {
    pushBack(item);
    return end();
  }
  node_t *newNode = new node_t;
  newNode->data = item;
  newNode->next = pos.nodeptr_;
  newNode->previous = pos.nodeptr_->previous;
  pos.nodeptr_->previous->next = newNode;
  pos.nodeptr_->previous = newNode;

  return pos;
}
template< class T >
void tampio::BidirectionalList< T >::deleteNode(const Iterator &pos)
{
  if (pos == begin())
  {
    deleteFront();
    return;
  }
  if (pos == beforeEnd())
  {
    deleteBack();
    return;
  }
  node_t *prev = pos.nodeptr_->previous;
  node_t *next = pos.nodeptr_->next;
  if (prev)
  {
    prev->next = next;
  }
  if (next)
  {
    next->previous = prev;
  }
  delete pos.nodeptr_;
}

template< class T >
void tampio::BidirectionalList< T >::print(std::ostream &pos) const
{
  Iterator i = begin();
  if (i != end())
  {
    pos << *(i++);
  }
  for (; i != end(); i++)
  {
    pos << " " << *i;
  }
}

#endif
