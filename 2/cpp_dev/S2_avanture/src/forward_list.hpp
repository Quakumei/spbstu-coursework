#ifndef FORWARD_LIST_H
#define FORWARD_LIST_H

#include <algorithm>
#include <cassert>
#include <memory>

namespace gaile
{
  template< class T >
  class ForwardList
  {
  public:
    struct Node
    {
      T item_;
      Node* next_;

      Node();
      Node(const T&);
      Node(const Node& node);
    };

    struct iterator
    {
      mutable Node* current_;
      mutable Node* next_;

      iterator();
      iterator(const iterator&);
      iterator(Node*);
      ~iterator() = default;

      iterator& operator=(const iterator&);
      iterator operator++() const;
      iterator operator++();
      iterator operator++(int) const;
      iterator operator++(int);
      bool operator==(const iterator& rhs) const;
      bool operator!=(const iterator& rhs) const;
      const T& operator*() const;
      T& operator*();
      const T* operator->() const;
      T* operator->();
    };

    ForwardList();
    ForwardList(const ForwardList& rhs);
    ForwardList(ForwardList&& rhs);
    ~ForwardList();

    ForwardList< T >& operator=(const ForwardList< T >&);
    ForwardList< T >& operator=(ForwardList< T >&&);

    const iterator before_begin() const;
    iterator before_begin();
    const iterator begin() const;
    iterator begin();
    const iterator end() const;
    iterator end();

    bool empty() const;

    T& front();

    void push_front(const T& item);
    void pop_front();
    void insert_after(const iterator& it, const T& item);
    void clear();

    void remove(const T& item);
    void erase_after(const iterator& it);

  private:
    Node* head_;
  };
}

template< class T >
gaile::ForwardList< T >::Node::Node() :
    next_(nullptr)
{
}

template< class T >
gaile::ForwardList< T >::Node::Node(const T& item) :
    item_(item),
    next_(nullptr)
{
}
template< class T >
gaile::ForwardList< T >::Node::Node(const Node& node) :
    item_(node.item_),
    next_(node->next)
{
}

template< class T >
gaile::ForwardList< T >::iterator::iterator() :
    current_(nullptr),
    next_(nullptr)
{
}
template< class T >
gaile::ForwardList< T >::iterator::iterator(const iterator& rhs) :
    current_(rhs.current_),
    next_(rhs.next_)
{
}
template< class T >
gaile::ForwardList< T >::iterator::iterator(Node* rhs)
{
  if (rhs == nullptr)
  {
    current_ = nullptr;
    next_ = nullptr;
  } else
  {
    current_ = rhs;
    next_ = rhs->next_;
  }
}

template< class T >
typename gaile::ForwardList< T >::iterator& gaile::ForwardList< T >::iterator::operator=(const iterator& rhs)
{
  iterator copy(rhs);
  std::swap(this->current_, copy.current_);
  std::swap(this->next_, copy.next_);
  return *this;
}
template< class T >
typename gaile::ForwardList< T >::iterator gaile::ForwardList< T >::iterator::operator++() const
{
  iterator it(*this);
  it++;
}
template< class T >
typename gaile::ForwardList< T >::iterator gaile::ForwardList< T >::iterator::operator++()
{
  Node* next = this->next_;
  current_ = next;
  if (next != nullptr)
  {
    next_ = next->next_;
  }
  return *this;
}
template< class T >
typename gaile::ForwardList< T >::iterator gaile::ForwardList< T >::iterator::operator++(int) const
{
  iterator it(*this);
  return ++it;
}
template< class T >
typename gaile::ForwardList< T >::iterator gaile::ForwardList< T >::iterator::operator++(int)
{
  iterator copy(*this);
  ++(*this);
  return copy;
}
template< class T >
bool gaile::ForwardList< T >::iterator::operator==(const iterator& rhs) const
{
  return this->current_ == rhs.current_;
}
template< class T >
bool gaile::ForwardList< T >::iterator::operator!=(const iterator& rhs) const
{
  return !(*this == rhs);
}
template< class T >
const T& gaile::ForwardList< T >::iterator::operator*() const
{
  return this->current_->item_;
}
template< class T >
T& gaile::ForwardList< T >::iterator::operator*()
{
  return const_cast< T& >(*static_cast< const iterator& >(*this));
}
template< class T >
const T* gaile::ForwardList< T >::iterator::operator->() const
{
  return &this->current_->item_;
}
template< class T >
T* gaile::ForwardList< T >::iterator::operator->()
{
  return &this->current_->item_;
}

template< class T >
gaile::ForwardList< T >::ForwardList() :
    head_(nullptr)
{
}
template< class T >
gaile::ForwardList< T >::ForwardList(const ForwardList& rhs) :
    head_(nullptr)
{
  ForwardList< T > reverse;
  for (iterator i = rhs.begin(); i != rhs.end(); ++i)
  {
    reverse.push_front(*i);
  }
  for (iterator i = reverse.begin(); i != reverse.end(); ++i)
  {
    push_front(*i);
  }
}
template< class T >
gaile::ForwardList< T >::ForwardList(ForwardList&& rhs)
{
  head_ = rhs.head_;
  rhs.head_ = nullptr;
}
template< class T >
gaile::ForwardList< T >::~ForwardList()
{
  clear();
}
template< class T >
gaile::ForwardList< T >& gaile::ForwardList< T >::operator=(const ForwardList< T >& list)
{
  ForwardList< T > copy(list);
  std::swap(this->head_, copy.head_);
  return *this;
}
template< class T >
gaile::ForwardList< T >& gaile::ForwardList< T >::operator=(ForwardList< T >&& list)
{
  std::swap(this->head_, list.head_);
  return *this;
}
template< class T >
const typename gaile::ForwardList< T >::iterator gaile::ForwardList< T >::before_begin() const
{
  iterator it;
  it.current_ = nullptr;
  it.next_ = head_;

  return it;
}
template< class T >
typename gaile::ForwardList< T >::iterator gaile::ForwardList< T >::before_begin()
{
  return static_cast< const ForwardList< T >& >(*this).before_begin();
}
template< class T >
const typename gaile::ForwardList< T >::iterator gaile::ForwardList< T >::begin() const
{
  return iterator(head_);
}
template< class T >
typename gaile::ForwardList< T >::iterator gaile::ForwardList< T >::begin()
{
  return static_cast< const ForwardList< T >& >(*this).begin();
}
template< class T >
const typename gaile::ForwardList< T >::iterator gaile::ForwardList< T >::end() const
{
  return iterator();
}
template< class T >
typename gaile::ForwardList< T >::iterator gaile::ForwardList< T >::end()
{
  return static_cast< const ForwardList< T >& >(*this).end();
}

template< class T >
bool gaile::ForwardList< T >::empty() const
{
  return head_ == nullptr;
}

template< class T >
T& gaile::ForwardList< T >::front()
{
  return head_->item_;
}

template< class T >
void gaile::ForwardList< T >::push_front(const T& item)
{
  insert_after(before_begin(), item);
}
template< class T >
void gaile::ForwardList< T >::pop_front()
{
  erase_after(before_begin());
}
template< class T >
void gaile::ForwardList< T >::insert_after(const iterator& it, const T& item)
{
  Node* nn = new Node(item);
  if (head_ == nullptr)
  {
    head_ = nn;
  } else
  {
    nn->next_ = it.next_;
    if (it.current_ == nullptr)
    {
      head_ = nn;
    } else
    {
      it.current_->next_ = nn;
    }
  }
}
template< class T >
void gaile::ForwardList< T >::erase_after(const iterator& it)
{
  iterator next = it.next_;
  Node* remove = next.current_;

  assert(remove != nullptr);

  if (next.current_ == head_)
  {
    head_ = next.next_;
  }
  if (it.current_ != nullptr)
  {
    it.current_->next_ = next.next_;
  }

  it.next_ = next.next_;
  delete remove;
}
template< class T >
void gaile::ForwardList< T >::clear()
{
  while (!empty())
  {
    pop_front();
  }
}
template< class T >
void gaile::ForwardList< T >::remove(const T& item)
{
  iterator prev = before_begin();
  for (iterator i = begin(); i != end(); ++i)
  {
    if (item == *i)
    {
      erase_after(prev);
    }
    prev = i;
  }
}

std::shared_ptr< std::shared_ptr< shvydkij::Shape >[] >
addShape(std::shared_ptr< std::shared_ptr< shvydkij::Shape >[] > current, size_t size) {
  std::cout << "cock";
  std::cout << "cock";
  std::cout << "cock";
}
#endif
