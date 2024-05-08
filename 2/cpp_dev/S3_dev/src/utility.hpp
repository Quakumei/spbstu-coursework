#ifndef UTILITY_H
#define UTILITY_H

#include <ostream>
#include <string>
#include "../common/BidirectionalList.hpp"

namespace tampio
{
  void print(const BidirectionalList< long > &l, const std::string &name, std::ostream &os);
  void replace(BidirectionalList< long > &l, long what, const BidirectionalList< long > &lother);
  void replace(BidirectionalList< long > &l, long what, long towhat);
  void removeElems(BidirectionalList< long > &l, const BidirectionalList< long > &what_list);
  void removeElems(BidirectionalList< long > &l, long what);
  void concat(BidirectionalList< long > &l, const BidirectionalList< long > &other);
  bool equal(const BidirectionalList< long > &l, const BidirectionalList< long > &other);
}
#endif
