#ifndef UTILITY_H
#define UTILITY_H

#include <ostream>
#include <string>
#include "../common/DictionaryBST.hpp"

namespace tampio
{
  using Dict = tampio::DictionaryBST< std::string, std::string >;
  using DictOfDict = tampio::DictionaryBST< std::string, Dict >;

  void print(const Dict& d, const std::string& name, std::ostream& os);
  Dict complement(const Dict&, const Dict&);
  Dict intersect(const Dict&, const Dict&);
  Dict unionDict(const Dict&, const Dict&);
}
#endif
