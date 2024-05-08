#include <ostream>
#include "utility.hpp"
#include "Dictionary.hpp"

void tampio::print(const tampio::Dict& d, const std::string& name, std::ostream& os)
{
  if (d.empty())
  {
    os << "<EMPTY>" << '\n';
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
  for (typename tampio::Dict::List::Iterator i = a.begin(); i != a.end(); i++)
  {
    if (!b.doesKeyExist(i->first))
    {
      res.push(i->first, i->second);
    }
  }
  for (typename tampio::Dict::List::Iterator i = b.begin(); i != b.end(); i++)
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
  for (typename tampio::Dict::List::Iterator i = b.begin(); i != b.end(); i++)
  {
    if (a.doesKeyExist(i->first))
    {
      res.push(i->first, i->second);
    }
  }
  for (typename tampio::Dict::List::Iterator i = a.begin(); i != a.end(); i++)
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
  for (typename tampio::Dict::List::Iterator i = b.begin(); i != b.end(); i++)
  {
    res.push(i->first, i->second);
  }
  for (typename tampio::Dict::List::Iterator i = a.begin(); i != a.end(); i++)
  {
    res.push(i->first, i->second);
  }
  return res;
}
