#ifndef LIST_H
#define LIST_H

#include <iostream>

namespace tampio
{
  template< class T >
  class ForwardList
  {
  private:
    struct node_t;

  public:
    ForwardList();
    ~ForwardList();
    ForwardList(const ForwardList &);
    ForwardList(ForwardList &&) noexcept;
    ForwardList &operator=(const ForwardList &);
    ForwardList &operator=(ForwardList &&) noexcept;

    void pushTail(const T &);
    void pushHead(const T &);

    // По аналогии с std::vector
    void rmFront();
    T top() const;
    T bottom() const;
    bool isEmpty() const noexcept;

    // S2 extension
    class Iterator
    {
    public:
      Iterator();
      Iterator(const Iterator &);
      Iterator(node_t *);
      ~Iterator() = default;
      const T &operator*() const;
      T &operator*();
      const T *operator->() const;
      T *operator->();
      Iterator &operator=(const Iterator &);
      Iterator &operator++();
      Iterator operator++(int);
      bool operator!=(const Iterator &) const;
      bool operator==(const Iterator &) const;

    private:
      friend ForwardList;
      node_t *cur_;
      node_t *next_;
    };

    const Iterator cbeforeBegin() const;
    Iterator beforeBegin();
    const Iterator cbegin() const;
    Iterator begin();
    const Iterator cend() const;
    Iterator end();

    const Iterator cfind() const;
    Iterator find();

    Iterator insertAfter(Iterator, const T &);
    bool remove(const T &item);

    void print(std::ostream &) const;

  private:
    struct node_t
    {
      T data;
      node_t *next;
    };
    node_t *head_;
    node_t *tail_;

    void swap(ForwardList &) noexcept;
  };
}

template< class T >
bool tampio::ForwardList< T >::remove(const T &item)
{
  if (head_ != nullptr)
  {
    node_t *currentNode = head_;
    if (head_->data == item)
    {
      head_ = head_->next;
      currentNode->next = nullptr;
      delete currentNode;
      return true;
    }
    while (currentNode->next != nullptr)
    {
      if (currentNode->next->data == item)
      {
        node_t *uslNode = currentNode->next;
        if (uslNode->next != nullptr)
        {
          currentNode->next = uslNode->next;
          uslNode->next = nullptr;
        } else
        {
          currentNode->next = nullptr;
        }
        delete uslNode;
        return false;
      }
      currentNode = currentNode->next;
    }
  }
  return false;
}

template< typename T >
void tampio::ForwardList< T >::print(std::ostream &stream) const
{
  node_t *temp = head_;
  while (temp)
  {
    if (temp->next == nullptr)
    {
      stream << temp->data;
    } else
    {
      stream << temp->data << " ";
    }
    temp = temp->next;
  }
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
  } else
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

// Iterator methods
template< class T >
const typename tampio::ForwardList< T >::Iterator tampio::ForwardList< T >::cbeforeBegin() const
{
  Iterator it;
  it.cur_ = nullptr;
  it.next_ = head_;
  return it;
};
template< class T >
typename tampio::ForwardList< T >::Iterator tampio::ForwardList< T >::beforeBegin()
{
  Iterator it;
  it.cur_ = nullptr;
  it.next_ = head_;
  return it;
};
template< class T >
const typename tampio::ForwardList< T >::Iterator tampio::ForwardList< T >::cbegin() const
{
  return Iterator(head_);
};
template< class T >
typename tampio::ForwardList< T >::Iterator tampio::ForwardList< T >::begin()
{
  return Iterator(head_);
};
template< class T >
const typename tampio::ForwardList< T >::Iterator tampio::ForwardList< T >::cend() const
{
  return Iterator(tail_);
};
template< class T >
typename tampio::ForwardList< T >::Iterator tampio::ForwardList< T >::end()
{
  return Iterator(tail_);
};

template< typename T >
tampio::ForwardList< T >::Iterator::Iterator() :
    cur_(nullptr),
    next_(nullptr)
{}
template< typename T >
tampio::ForwardList< T >::Iterator::Iterator(const Iterator &other) :
    cur_(other.cur_),
    next_(other.next_)
{}
template< typename T >
tampio::ForwardList< T >::Iterator::Iterator(node_t *node)
{
  if (node == nullptr)
  {
    cur_ = nullptr;
    next_ = nullptr;
  } else
  {
    cur_ = node;
    next_ = node->next;
  }
}
template< typename T >
T &tampio::ForwardList< T >::Iterator::operator*()
{
  return cur_->data;
}
template< typename T >
const T &tampio::ForwardList< T >::Iterator::operator*() const
{
  return cur_->data;
}
template< typename T >
typename tampio::ForwardList< T >::Iterator &tampio::ForwardList< T >::Iterator::operator=(const Iterator &other)
{
  Iterator newIt(other);
  std::swap(cur_, newIt.cur_);
  std::swap(next_, newIt.next_);
  return *this;
}
template< typename T >
bool tampio::ForwardList< T >::Iterator::operator!=(const Iterator &lhs) const
{
  return !(*this == lhs);
}
template< typename T >
bool tampio::ForwardList< T >::Iterator::operator==(const Iterator &lhs) const
{
  return cur_ == lhs.cur_;
}
template< typename T >
typename tampio::ForwardList< T >::Iterator &tampio::ForwardList< T >::Iterator::operator++()
{
  cur_ = next_;
  if (next_ != nullptr)
  {
    next_ = next_->next;
  }
  return *this;
}
template< typename T >
typename tampio::ForwardList< T >::Iterator tampio::ForwardList< T >::Iterator::operator++(int)
{
  Iterator result(*this);
  ++(*this);
  return result;
}
template< typename T >
T *tampio::ForwardList< T >::Iterator::operator->()
{
  return std::addressof(cur_->data);
}
template< typename T >
const T *tampio::ForwardList< T >::Iterator::operator->() const
{
  return std::addressof(cur_->data);
}

template< typename T >
typename tampio::ForwardList< T >::Iterator
tampio::ForwardList< T >::insertAfter(typename ForwardList< T >::Iterator pos, const T &item)
{
  if (pos == cbeforeBegin())
  {
    if (head_ != nullptr)
    {
      node_t *exHead = head_;
      head_ = new node_t;
      head_->data = item;
      head_->next = exHead;
      return begin();
    } else
    {
      head_ = new node_t;
      head_->data = item;
      return begin();
    }
  } else
  {
    node_t *temp = pos.next_;
    pos.next_ = new node_t;
    pos.next_->data = item;
    pos.cur_->next = pos.next_;
    ++pos;
    if (temp != nullptr)
    {
      pos.next_ = temp;
      pos.cur_->next = pos.next_;
    }
    return pos;
  }
}

#endif
