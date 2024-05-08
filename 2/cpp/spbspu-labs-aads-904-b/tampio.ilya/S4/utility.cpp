#include <ostream>
#include "../common/DictionaryBST.hpp"
#include "utility.hpp"
#include "Logger.hpp"

void tampio::print(const tampio::Dict& d, const std::string& name, std::ostream& os)
{
  if (d.empty())
  {
    Logger::log(Logger::Message::EMPTY, os);
    return;
  }
  os << name << ' ';
  d.print(os);
  os << '\n';
  return;
}
tampio::Dict tampio::complement(const Dict& a, const Dict& b)
{
  Dict res;
  for (typename tampio::Dict::BST::ConstIterator i = a.cbegin(); i != a.cend(); i++)
  {
    if (!b.doesKeyExist(i->first))
    {
      res.push(i->first, i->second);
    }
  }
  for (typename tampio::Dict::BST::ConstIterator i = b.cbegin(); i != b.cend(); i++)
  {
    if (!a.doesKeyExist(i->first))
    {
      res.push(i->first, i->second);
    }
  }
  return res;
}
tampio::Dict tampio::intersect(const Dict& a, const Dict& b)
{
  Dict res;
  for (typename tampio::Dict::BST::ConstIterator i = b.cbegin(); i != b.cend(); i++)
  {
    if (a.doesKeyExist(i->first))
    {
      res.push(i->first, i->second);
    }
  }
  for (typename tampio::Dict::BST::ConstIterator i = a.cbegin(); i != a.cend(); i++)
  {
    if (b.doesKeyExist(i->first))
    {
      res.push(i->first, i->second);
    }
  }
  return res;
}

tampio::Dict tampio::unionDict(const Dict& a, const Dict& b)
{
  Dict res;
  for (typename tampio::Dict::BST::ConstIterator i = b.cbegin(); i != b.cend(); i++)
  {
    res.push(i->first, i->second);
  }
  for (typename tampio::Dict::BST::ConstIterator i = a.cbegin(); i != a.cend(); i++)
  {
    res.push(i->first, i->second);
  }
  return res;
}
