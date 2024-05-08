#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <map>
#include <string>

#include "dictionary.hpp"

namespace gaile
{
  using dict_t = gaile::Dictionary< std::string, std::string >;
  using ddict_t = gaile::Dictionary< std::string, dict_t >;

  void print(dict_t& list, std::ostream& os);
  dict_t complement(dict_t& first, dict_t& second);
  dict_t intersect(dict_t& first, dict_t& second);
  dict_t unionDict(dict_t& first, dict_t& second);
}
#endif
