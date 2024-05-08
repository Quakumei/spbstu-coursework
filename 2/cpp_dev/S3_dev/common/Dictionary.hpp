#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <ostream>
#include <stdexcept>
#include <utility>
#include "BidirectionalList.hpp"
#include "ForwardList.hpp"

namespace tampio
{
  template< class Key, class Value, class Compare = std::less< Key > >
  class Dictionary
  {
  public:
    using List = BidirectionalList< std::pair< Key, Value > >;
    using Dict = Dictionary< Key, Value, Compare >;

    Dictionary();
    ~Dictionary() = default;
    Dictionary(const Dict &other);
    Dictionary(Dict &&other);
    Dict &operator=(const Dict &other) = default;
    Dict &operator=(Dict &&other) = default;

    void push(const Key &, const Value &);
    Value get(const Key &) const;
    Value &getRef(const Key &);
    Value drop(const Key &);
    bool doesKeyExist(const Key &) const;
    bool empty() const;
    void print(std::ostream &) const;

    typename List::Iterator find(const Key &) const;
    typename List::Iterator begin();
    typename List::Iterator end();
    const typename List::Iterator begin() const;
    const typename List::Iterator end() const;

  private:
    Compare cmp_;
    List data_;
  };
}
template< class Key, class Value, class Compare >
bool tampio::Dictionary< Key, Value, Compare >::empty() const
{
  return data_.begin() == data_.end();
}
template< class Key, class Value, class Compare >
void tampio::Dictionary< Key, Value, Compare >::print(std::ostream &os) const
{
  for (typename List::Iterator i = data_.begin(); i != data_.end(); i++)
  {
    os << i->first << ' ' << i->second;
    if ((i + 1) != data_.end())
    {
      os << ' ';
    }
  }
}
template< class Key, class Value, class Compare >
tampio::Dictionary< Key, Value, Compare >::Dictionary() :
    cmp_(Compare()),
    data_()
{
}
template< class Key, class Value, class Compare >
tampio::Dictionary< Key, Value, Compare >::Dictionary(const Dict &other) :
    cmp_(Compare()),
    data_(other.data_)
{
}
template< class Key, class Value, class Compare >
tampio::Dictionary< Key, Value, Compare >::Dictionary(Dict &&other) :
    cmp_(Compare()),
    data_(other.data_)
{
}
template< class Key, class Value, class Compare >
bool tampio::Dictionary< Key, Value, Compare >::doesKeyExist(const Key &key) const
{
  return find(key) != typename List::Iterator();
}
template< class Key, class Value, class Compare >
void tampio::Dictionary< Key, Value, Compare >::push(const Key &key, const Value &value)
{
  if (doesKeyExist(key))
  {
    find(key)->second = value;
    return;
  }
  std::pair< Key, Value > tempPair(key, value);
  typename List::Iterator it = data_.begin();
  while (it != data_.end())
  {
    if (cmp_(tempPair.first, it->first))
    {
      if (it + 1 != data_.end())
      {
        data_.insertBefore(it + 1, tempPair);
      }
    }
    ++it;
  }
  if (it == data_.end())
  {
    data_.pushBack(tempPair);
  }
  return;
}
template< class Key, class Value, class Compare >
Value tampio::Dictionary< Key, Value, Compare >::get(const Key &key) const
{
  if (!doesKeyExist(key))
  {
    throw std::out_of_range("No such key in the dict. (get())");
  }
  return find(key)->second;
}
template< class Key, class Value, class Compare >
Value &tampio::Dictionary< Key, Value, Compare >::getRef(const Key &key)
{
  if (!doesKeyExist(key))
  {
    throw std::out_of_range("No such key in the dict. (get())");
  }
  return find(key)->second;
}
template< class Key, class Value, class Compare >
Value tampio::Dictionary< Key, Value, Compare >::drop(const Key &key)
{
  if (!doesKeyExist(key))
  {
    throw std::out_of_range("No such key in the dict. (get())");
  }
  typename List::Iterator it = find(key);
  Value temp = it->second;
  data_.deleteNode(it);
  return temp;
}
template< class Key, class Value, class Compare >
typename tampio::Dictionary< Key, Value, Compare >::List::Iterator tampio::Dictionary< Key, Value, Compare >::find(
    const Key &key) const
{
  for (typename List::Iterator it = data_.begin(); it != data_.end(); it++)
  {
    if (it->first == key)
    {
      return it;
    }
  }
  return typename List::Iterator();
}
template< class Key, class Value, class Compare >
typename tampio::Dictionary< Key, Value, Compare >::List::Iterator tampio::Dictionary< Key, Value, Compare >::begin()
{
  return data_.begin();
}
template< class Key, class Value, class Compare >
typename tampio::Dictionary< Key, Value, Compare >::List::Iterator tampio::Dictionary< Key, Value, Compare >::end()
{
  return data_.end();
}
template< class Key, class Value, class Compare >
const typename tampio::Dictionary< Key, Value, Compare >::List::Iterator
tampio::Dictionary< Key, Value, Compare >::begin() const
{
  return data_.begin();
}
template< class Key, class Value, class Compare >
const typename tampio::Dictionary< Key, Value, Compare >::List::Iterator
tampio::Dictionary< Key, Value, Compare >::end() const
{
  return data_.end();
}

#endif
