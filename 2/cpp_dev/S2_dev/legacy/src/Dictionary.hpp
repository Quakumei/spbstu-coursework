#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdexcept>
#include <utility>

#include "ForwardList.hpp"

namespace tampio
{
  template< typename Key, typename Value, typename Compare = std::less< Key > >
  class Dictionary
  {
  public:
    void push(const Key& k, const Value& v);
    Value get(const Key& k) const;
    void drop(const Key& k);

    bool doesExist(const Key& k) const;

  private:
    Compare compare;
    ForwardList< std::pair< Key, Value > > listData_;
  };

  template< typename Key, typename Value, typename Compare >
  void tampio::Dictionary< Key, Value, Compare >::push(const Key& key, const Value& value)
  {
    typename ForwardList< std::pair< Key, Value > >::Iterator keysIt = find(key);
    if (keysIt != cend())
    {
      return;
    }
    std::pair< Key, Value > tempKeyValue(key, value);
    // TODO: Make beforeBegin
    typename ForwardList< std::pair< Key, Value > >::Iterator beforeIt = listData_.beforeBegin();
    // typename ForwardList< std::pair< Key, Value > >::Iterator beforeIt = list_.beforeBegin();
    while (it != cend())
    {
      if (compare(tempKeyValue.first, (beforeIt + 1)->first))
      {
        // TODO: Make insertAfter
        listData_.insertAfter(beforeIt, tempKeyValue);
        return;
      }
      // ++it;
      ++beforeIt;
    }
    list_.insertAfter(beforeIt, tempKeyValue);
    return;
  }

  template< typename Key, typename Value, typename Compare >
  Value tampio::Dictionary< Key, Value, Compare >::get(const Key& key) const
  {
    for (typename ForwardList < std::pair< Key, Value >::Iterator it = listData_.begin(); it != listData_.end(); it++)
    {
      if (it->first == key)
      {
        return it->second;
      }
    }
    throw std::out_of_range("No key in the dict.");
  }

  template< typename Key, typename Value, typename Compare >
  bool tampio::Dictionary< Key, Value, Compare >::doesExist(const Key& key) const
  {
    for (typename ForwardList < std::pair< Key, Value >::Iterator it = listData_.begin(); it != listData_.end(); it++)
    {
      if (it->first == key)
      {
        return true;
      }
    }
    return false;
  }

  template< typename Key, typename Value, typename Compare >
  void tampio::Dictionary< Key, Value, Compare >::drop(const Key& key) const
  {
    for (typename ForwardList < std::pair< Key, Value >::Iterator it = listData_.begin(); it != listData_.end(); it++)
    {
      if (it->first == key)
      {
        listData_.remove();
      }
    }
  }
}

#endif
