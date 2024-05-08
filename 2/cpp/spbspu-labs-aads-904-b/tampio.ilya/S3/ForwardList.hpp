#ifndef FORWARDLIST_H
#define FORWARDLIST_H

#include <stdexcept>
#include <utility>
namespace tampio
{
  template< class T >
  class ForwardList
  {
  public:
    ForwardList();
    ForwardList(const ForwardList &);
    ForwardList(ForwardList &&) noexcept;
    ~ForwardList();
    ForwardList &operator=(const ForwardList &);
    ForwardList &operator=(ForwardList &&) noexcept;

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
    Iterator beforeEnd();
    Iterator beforeBegin();
    const Iterator begin() const;
    const Iterator end() const;
    const Iterator beforeEnd() const;
    const Iterator beforeBegin() const;
    const Iterator insertAfter(const Iterator &, const T &);
    void deleteNode(const Iterator &);

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

  template< class T >
  class ForwardList< T >::Iterator
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
    Iterator operator+(int);

  private:
    node_t *nodeptr_;
    node_t *nextptr_;
    friend ForwardList;
  };
}
template< class T >
void tampio::ForwardList< T >::deleteFront()
{
  if (empty())
  {
    throw std::logic_error("ForwardList is empty");
  }
  node_t *temp = head_;
  head_ = (head_ == tail_) ? tail_ = nullptr : head_->next;
  delete temp;
}
template< class T >
void tampio::ForwardList< T >::deleteBack()
{
  if (empty())
  {
    throw std::logic_error("ForwardList is empty");
  }
  node_t *temp = tail_;
  node_t *beforeTemp = nullptr;
  for (Iterator i = begin(); i != end(); i++)
  {
    if (i.nextptr_ == temp)
    {
      beforeTemp = i.nodeptr_;
      beforeTemp->next = nullptr;
      break;
    }
  }
  tail_ = (head_ == tail_) ? head_ = nullptr : beforeTemp;
  delete temp;
}
template< class T >
T tampio::ForwardList< T >::front() const
{
  return head_->data;
}
template< class T >
void tampio::ForwardList< T >::pushBack(const T &item)
{
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
}
template< class T >
void tampio::ForwardList< T >::pushFront(const T &val)
{
  node_t *newNode = new node_t;
  newNode->data = val;
  newNode->next = head_;
  if (empty())
  {
    tail_ = head_ = newNode;
  }
  else
  {
    head_ = newNode;
  }
}
template< class T >
T tampio::ForwardList< T >::tail() const
{
  return tail_->data;
}
template< class T >
tampio::ForwardList< T >::ForwardList() :
    head_(nullptr),
    tail_(nullptr)
{
}
template< class T >
tampio::ForwardList< T >::ForwardList(const ForwardList &forwardList) :
    head_(nullptr),
    tail_(nullptr)
{
  tampio::ForwardList< T > temp;
  node_t *src = forwardList.head_;
  while (src)
  {
    temp.pushBack(src->data);
    src = src->next;
  }
  swap(temp);
}
template< class T >
tampio::ForwardList< T >::ForwardList(ForwardList &&forwardList) noexcept :
    head_(nullptr),
    tail_(nullptr)
{
  swap(forwardList);
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
tampio::ForwardList< T > &tampio::ForwardList< T >::operator=(const ForwardList &forwardList)
{
  if (this == &forwardList)
  {
    return *this;
  }
  tampio::ForwardList< T > tempForwardList(forwardList);
  swap(tempForwardList);
  return *this;
}
template< class T >
tampio::ForwardList< T > &tampio::ForwardList< T >::operator=(ForwardList &&forwardList) noexcept
{
  swap(forwardList);
  return *this;
}
template< class T >
bool tampio::ForwardList< T >::empty() const noexcept
{
  return !head_;
}
template< class T >
void tampio::ForwardList< T >::swap(ForwardList &forwardList) noexcept
{
  std::swap(head_, forwardList.head_);
  std::swap(tail_, forwardList.tail_);
}

template< class T >
tampio::ForwardList< T >::Iterator::Iterator() :
    nodeptr_(nullptr),
    nextptr_(nullptr){};
template< class T >
tampio::ForwardList< T >::Iterator::Iterator(const Iterator &other) :
    nodeptr_(other.nodeptr_),
    nextptr_(other.nextptr_){};
template< class T >
tampio::ForwardList< T >::Iterator::Iterator(node_t *node)
{
  nodeptr_ = node;
  nextptr_ = (node) ? node->next : nullptr;
};

template< class T >
typename tampio::ForwardList< T >::Iterator &tampio::ForwardList< T >::Iterator::operator=(const Iterator &other)
{
  nodeptr_ = other.nodeptr_;
  nextptr_ = other.nextptr_;
  return *this;
}

template< class T >
T &tampio::ForwardList< T >::Iterator::operator*()
{
  return nodeptr_->data;
}
template< class T >
const T &tampio::ForwardList< T >::Iterator::operator*() const
{
  return nodeptr_->data;
}
template< class T >
T *tampio::ForwardList< T >::Iterator::operator->()
{
  return &(nodeptr_->data);
}
template< class T >
const T *tampio::ForwardList< T >::Iterator::operator->() const
{
  return &(nodeptr_->data);
}
template< class T >
bool tampio::ForwardList< T >::Iterator::operator==(const Iterator &oth) const
{
  return nodeptr_ == oth.nodeptr_ && nextptr_ == oth.nextptr_;
}
template< class T >
bool tampio::ForwardList< T >::Iterator::operator!=(const Iterator &oth) const
{
  return !(nodeptr_ == oth.nodeptr_);
}
template< class T >
typename tampio::ForwardList< T >::Iterator &tampio::ForwardList< T >::Iterator::operator++()
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
typename tampio::ForwardList< T >::Iterator tampio::ForwardList< T >::Iterator::operator++(int)
{
  Iterator temp(nodeptr_);
  ++(*this);
  return temp;
}
template< class T >
typename tampio::ForwardList< T >::Iterator tampio::ForwardList< T >::Iterator::operator+(int n)
{
  if (n == 0)
  {
    return *this;
  }
  else if (n < 0)
  {
    throw std::logic_error("traversing back isn't possible in forward list");
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
typename tampio::ForwardList< T >::Iterator tampio::ForwardList< T >::begin()
{
  return Iterator(head_);
}
template< class T >
typename tampio::ForwardList< T >::Iterator tampio::ForwardList< T >::end()
{
  return Iterator();
}
template< class T >
typename tampio::ForwardList< T >::Iterator tampio::ForwardList< T >::beforeEnd()
{
  return Iterator(tail_);
}
template< class T >
typename tampio::ForwardList< T >::Iterator tampio::ForwardList< T >::beforeBegin()
{
  Iterator it;
  it.nextptr_ = head_;
  return it;
}
template< class T >
const typename tampio::ForwardList< T >::Iterator tampio::ForwardList< T >::begin() const
{
  return Iterator(head_);
}
template< class T >
const typename tampio::ForwardList< T >::Iterator tampio::ForwardList< T >::end() const
{
  return Iterator();
}
template< class T >
const typename tampio::ForwardList< T >::Iterator tampio::ForwardList< T >::beforeEnd() const
{
  return Iterator(tail_);
}
template< class T >
const typename tampio::ForwardList< T >::Iterator tampio::ForwardList< T >::beforeBegin() const
{
  Iterator it;
  it.nextptr_ = head_;
  return it;
}

template< class T >
const typename tampio::ForwardList< T >::Iterator tampio::ForwardList< T >::insertAfter(const Iterator &pos,
    const T &item)
{
  if (pos == beforeBegin())
  {
    pushFront(item);
    return begin();
  }
  else if (pos == beforeEnd())
  {
    pushBack(item);
    return end();
  }
  node_t *newNode = new node_t;
  newNode->next = pos.nextptr_;
  newNode->data = item;
  pos.nodeptr_->next = newNode;
  return pos;
}
template< class T >
void tampio::ForwardList< T >::deleteNode(const Iterator &pos)
{
  for (Iterator i = beforeBegin(); (i + 1) != end(); i++)
  {
    if ((i + 1) == pos)
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
      i.nodeptr_->next = i.nextptr_->next;
      delete i.nextptr_;
      return;
    }
  }
  throw std::logic_error("No such node (deleteNode(Iterator))");
}

#endif
