#include "DataStruct.hpp"
#include <bitset>
#include "iofmtguard.hpp"
#include "LongLongIO.hpp"
#include "UnsignedLongLongIO.hpp"
#include "DelimiterIO.hpp"
#include "StringIO.hpp"

std::istream& tampio::operator>>(std::istream& in, DataStruct& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  DataStruct input;
  bool key1 = false, key2 = false, key3 = false;
  {
    using sep = DelimeterIO;
    using sll = LongLongIO;
    using ull = UnsignedLongLongIO;
    using str = StringIO;
    in >> sep{'('} >> sep{':'};
    for (int i = 0; i < 3; i++)
    {
      std::string label = "";
      in >> label;
      if (label == "key1")
      {
        in >> sll{input.key1} >> sep{':'};
        key1 = true;
      }
      else if (label == "key2")
      {
        in >> ull{input.key2} >> sep{':'};
        key2 = true;
      }
      else if (label == "key3")
      {
        in >> str{input.key3} >> sep{':'};
        key3 = true;
      }
    }
    in >> sep{')'};
  }
  if (in && key1 && key2 && key3)
  {
    dest = input;
  }
  return in;
}

std::ostream& tampio::operator<<(std::ostream& out, const DataStruct& src)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  iofmtguard fmtguard(out);
  out << "(:key1 " << src.key1 << "ll";
  std::string binary = static_cast< std::bitset< 32 > >(src.key2).to_string();
  binary.erase(0, binary.find_first_not_of('0'));
  out << ":key2 0b0" << binary;
  out << ":key3 \"" << src.key3 << "\":)";
  return out;
}

bool tampio::DataStruct::operator<(const DataStruct& oth) const
{
  if (this->key1 == oth.key1)
  {
    if (this->key2 == oth.key2)
    {
      return this->key3.size() < oth.key3.size();
    }
    return this->key2 < oth.key2;
  }
  return this->key1 < oth.key1;
}
