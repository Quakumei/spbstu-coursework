#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP

#include <iosfwd>
#include <string>

namespace tampio
{
  struct DataStruct
  {
    long long key1 = 0;
    unsigned long long key2 = 0;
    std::string key3 = "";
    bool operator<(const DataStruct&) const;
  };
  std::istream& operator>>(std::istream& in, DataStruct& dest);
  std::ostream& operator<<(std::ostream& out, const DataStruct& dest);
}

#endif
