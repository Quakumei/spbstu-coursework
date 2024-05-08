#ifndef DICTIONARY_BST_HPP
#define DICTIONARY_BST_HPP

#include <ostream>
#include <stdexcept>
#include "BinarySearchTree.hpp"

namespace tampio
{
  template< typename Key, typename Value, typename Compare = std::less< Key > >
  class DictionaryBST
  {
  public:
    using BST = BinarySearchTree< Key, Value, Compare >;

    DictionaryBST() = default;
    ~DictionaryBST() = default;
    DictionaryBST(const DictionaryBST& other);
    DictionaryBST(DictionaryBST&& other) noexcept = default;
    DictionaryBST& operator=(const DictionaryBST& other);

    bool operator==(const DictionaryBST& other) const;
    bool operator!=(const DictionaryBST& other) const;

    void push(const Key& key, const Value& value);
    Value get(const Key&) const;
    Value& getRef(const Key&);
    Value drop(const Key& key);
    bool empty() const noexcept;
    bool doesKeyExist(const Key&) const;
    void print(std::ostream&) const;

    typename BST::Iterator find(const Key& key);
    typename BST::Iterator begin();
    typename BST::Iterator end();
    typename BST::ConstIterator cfind(const Key& key) const;
    typename BST::ConstIterator cbegin() const;
    typename BST::ConstIterator cend() const;

  private:
    BST data_;
    Compare cmp_;
  };
}

template< class Key, class Value, class Compare >
bool tampio::DictionaryBST< Key, Value, Compare >::doesKeyExist(const Key& key) const
{
  return cfind(key) != cend();
}

template< class Key, class Value, class Compare >
void tampio::DictionaryBST< Key, Value, Compare >::print(std::ostream& os) const
{
  typename BST::ConstIterator i = data_.cbegin();
  if (i != data_.cend())
  {
    os << i->first << ' ' << i->second;
  }
  while (++i != data_.cend())
  {
    os << ' ' << i->first << ' ' << i->second;
  }
}

template< typename Key, typename Value, typename Compare >
tampio::DictionaryBST< Key, Value, Compare >::DictionaryBST(const DictionaryBST& other) :
    data_(other.data_),
    cmp_(other.cmp_)
{
}

template< typename Key, typename Value, typename Compare >
tampio::DictionaryBST< Key, Value, Compare >& tampio::DictionaryBST< Key, Value, Compare >::operator=(
    const DictionaryBST& other)
{
  DictionaryBST< Key, Value, Compare > newDict(other);
  std::swap(data_, newDict.data_);
  std::swap(cmp_, newDict.cmp_);
  return *this;
}

template< typename Key, typename Value, typename Compare >
bool tampio::DictionaryBST< Key, Value, Compare >::operator==(const DictionaryBST& other) const
{
  return data_ == other.data_;
}

template< typename Key, typename Value, typename Compare >
bool tampio::DictionaryBST< Key, Value, Compare >::operator!=(const DictionaryBST& other) const
{
  return !(*this == other);
}

template< typename Key, typename Value, typename Compare >
void tampio::DictionaryBST< Key, Value, Compare >::push(const Key& key, const Value& value)
{
  data_.push(key, value);
}

template< typename Key, typename Value, typename Compare >
Value tampio::DictionaryBST< Key, Value, Compare >::drop(const Key& key)
{
  typename BST::Iterator it = find(key);
  if (it != end())
  {
    Value temp = it->second;
    data_.dropKey(it->first);
    return temp;
  }
}

template< class Key, class Value, class Compare >
Value& tampio::DictionaryBST< Key, Value, Compare >::getRef(const Key& key)
{
  if (empty())
  {
    throw std::logic_error("Dictionary is empty (getRef)");
  }
  typename BST::Iterator it = find(key);
  if (it == end())
  {
    throw std::logic_error("Key not found (getRef)");
  }
  return it->second;
}

template< class Key, class Value, class Compare >
Value tampio::DictionaryBST< Key, Value, Compare >::get(const Key& key) const
{
  if (empty())
  {
    throw std::logic_error("Dictionary is empty (get)");
  }
  typename BST::ConstIterator it = cfind(key);
  if (it == cend())
  {
    throw std::logic_error("Key not found (get)");
  }
  return it->second;
}

template< typename Key, typename Value, typename Compare >
typename tampio::BinarySearchTree< Key, Value, Compare >::Iterator tampio::DictionaryBST< Key, Value, Compare >::find(
    const Key& key)
{
  if (empty())
  {
    return end();
  }
  typename BST::Iterator i = begin();
  while (i != end())
  {
    if (i->first == key)
    {
      break;
    }
    i++;
  }
  return i;
}

template< typename Key, typename Value, typename Compare >
typename tampio::BinarySearchTree< Key, Value, Compare >::ConstIterator
tampio::DictionaryBST< Key, Value, Compare >::cfind(const Key& key) const
{
  if (empty())
  {
    return cend();
  }
  for (typename BST::ConstIterator i = cbegin(); i != cend(); i++)
  {
    if (i->first == key)
    {
      return i;
    }
  }
  return cend();
}

template< typename Key, typename Value, typename Compare >
typename tampio::BinarySearchTree< Key, Value, Compare >::Iterator tampio::DictionaryBST< Key, Value, Compare >::begin()
{
  return data_.begin();
}

template< typename Key, typename Value, typename Compare >
typename tampio::BinarySearchTree< Key, Value, Compare >::Iterator tampio::DictionaryBST< Key, Value, Compare >::end()
{
  return data_.end();
}

template< typename Key, typename Value, typename Compare >
typename tampio::BinarySearchTree< Key, Value, Compare >::ConstIterator
tampio::DictionaryBST< Key, Value, Compare >::cbegin() const
{
  return data_.cbegin();
}

template< typename Key, typename Value, typename Compare >
typename tampio::BinarySearchTree< Key, Value, Compare >::ConstIterator
tampio::DictionaryBST< Key, Value, Compare >::cend() const
{
  return data_.cend();
}

template< typename Key, typename Value, typename Compare >
bool tampio::DictionaryBST< Key, Value, Compare >::empty() const noexcept
{
  return data_.empty();
}
#endif
