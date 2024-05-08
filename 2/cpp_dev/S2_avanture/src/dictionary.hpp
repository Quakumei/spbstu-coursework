#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <algorithm>
#include <functional>

#include "forward_list.hpp"

namespace gaile
{
  template< class Key, class Value, class Compare = std::less< Key > >
  class Dictionary
  {
  public:
    using node_t = std::pair< Key, Value >;
    using list_t = gaile::ForwardList< node_t >;
    using iterator = typename list_t::iterator;

    Dictionary();
    Dictionary(const Dictionary< Key, Value, Compare >&);
    Dictionary(Dictionary< Key, Value, Compare >&&);
    ~Dictionary() = default;

    void operator=(const Dictionary< Key, Value, Compare >&);
    void operator=(Dictionary< Key, Value, Compare >&&);

    Value& operator[](const Key&);

    const iterator begin() const;
    iterator begin();
    const iterator end() const;
    iterator end();

    iterator find(const Key&);
    void erase(const Key&);

    bool empty() const;
    void reverse();

  private:
    list_t db_;
    Compare cmp_;

    void insert(const node_t& node);
  };
}

template< class Key, class Value, class Compare >
gaile::Dictionary< Key, Value, Compare >::Dictionary() :
    db_(),
    cmp_(Compare())
{}
template< class Key, class Value, class Compare >
gaile::Dictionary< Key, Value, Compare >::Dictionary(const Dictionary< Key, Value, Compare >& d) :
    db_(d.db_),
    cmp_(Compare())
{}
template< class Key, class Value, class Compare >
gaile::Dictionary< Key, Value, Compare >::Dictionary(Dictionary< Key, Value, Compare >&& d) :
    db_(d.db_),
    cmp_(Compare())
{
  d.db_.clear();
}
template< class Key, class Value, class Compare >
void gaile::Dictionary< Key, Value, Compare >::operator=(const Dictionary< Key, Value, Compare >& d)
{
  Dictionary< Key, Value, Compare > copy(d);
  swap(this->cmp_, copy.cmp_);
  this->db_ = move(copy.db_);
}
template< class Key, class Value, class Compare >
void gaile::Dictionary< Key, Value, Compare >::operator=(Dictionary< Key, Value, Compare >&& d)
{
  Dictionary< Key, Value, Compare > copy(d);
  swap(this->cmp_, copy.cmp_);
  this->db_ = move(copy.db_);

  d.db_.clear();
}

template< class Key, class Value, class Compare >
Value& gaile::Dictionary< Key, Value, Compare >::operator[](const Key& key)
{
  iterator it = find(key);
  if (it == end())
  {
    Value value;
    node_t node = {key, value};
    insert(node);
    return find(key)->second;
  }
  return it->second;
}
template< class Key, class Value, class Compare >
const typename gaile::Dictionary< Key, Value, Compare >::iterator
gaile::Dictionary< Key, Value, Compare >::begin() const
{
  return db_.begin();
}
template< class Key, class Value, class Compare >
typename gaile::Dictionary< Key, Value, Compare >::iterator gaile::Dictionary< Key, Value, Compare >::begin()
{
  return db_.begin();
}
template< class Key, class Value, class Compare >
const typename gaile::Dictionary< Key, Value, Compare >::iterator gaile::Dictionary< Key, Value, Compare >::end() const
{
  return db_.end();
}
template< class Key, class Value, class Compare >
typename gaile::Dictionary< Key, Value, Compare >::iterator gaile::Dictionary< Key, Value, Compare >::end()
{
  return db_.end();
}
template< class Key, class Value, class Compare >
typename gaile::Dictionary< Key, Value, Compare >::iterator gaile::Dictionary< Key, Value, Compare >::find(
    const Key& key)
{
  for (typename list_t::iterator i = db_.begin(); i != db_.end(); ++i)
  {
    if (i->first == key)
    {
      return i;
    }
  }
  return end();
}
template< class Key, class Value, class Compare >
void gaile::Dictionary< Key, Value, Compare >::erase(const Key& key)
{
  iterator it = find(key);
  if (it != end())
  {
    db_.remove(*it);
  }
}
template< class Key, class Value, class Compare >
bool gaile::Dictionary< Key, Value, Compare >::empty() const
{
  return db_.empty();
}

template< class Key, class Value, class Compare >
void gaile::Dictionary< Key, Value, Compare >::insert(const node_t& node)
{
  iterator prev = db_.before_begin();
  for (iterator i = db_.begin(); i != db_.end(); ++i)
  {
    if (cmp_(node.first, i->first))
    {
      db_.insert_after(prev, node);
      return;
    }
    prev = i;
  }
  db_.insert_after(prev, node);
}
#endif
