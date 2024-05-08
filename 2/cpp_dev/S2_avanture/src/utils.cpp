#include "utils.hpp"

void gaile::print(dict_t& list, std::ostream& os)
{
  if (list.empty())
  {
    std::cout << "<EMPTY>" << std::endl;
    return;
  }
  for (dict_t::iterator i = list.begin(); i != list.end(); i++)
  {
    os << (i == list.begin() ? "" : " ") << i->first << ' ' << i->second;
  }
  std::cout << std::endl;
}
gaile::dict_t gaile::complement(dict_t& first, dict_t& second)
{
  dict_t ndb;

  for (dict_t::iterator i = first.begin(); i != first.end(); i++)
  {
    bool isFind = false;
    for (dict_t::iterator j = second.begin(); j != second.end(); j++)
    {
      if (i->first == j->first)
      {
        isFind = true;
        break;
      }
    }
    if (!isFind)
    {
      ndb[i->first] = i->second;
    }
  }
  for (dict_t::iterator i = second.begin(); i != second.end(); i++)
  {
    bool isFind = false;
    for (dict_t::iterator j = first.begin(); j != first.end(); j++)
    {
      if (i->first == j->first)
      {
        isFind = true;
        break;
      }
    }
    if (!isFind)
    {
      ndb[i->first] = i->second;
    }
  }

  return ndb;
}
gaile::dict_t gaile::intersect(dict_t& first, dict_t& second)
{
  dict_t ndb;

  for (dict_t::iterator i = first.begin(); i != first.end(); i++)
  {
    if (second.find(i->first) != second.end())
    {
      ndb[i->first] = i->second;
    }
  }
  return ndb;
}
gaile::dict_t gaile::unionDict(dict_t& first, dict_t& second)
{
  dict_t ndb = second;

  for (dict_t::iterator i = first.begin(); i != first.end(); i++)
  {
    ndb[i->first] = i->second;
  }
  return ndb;
}
