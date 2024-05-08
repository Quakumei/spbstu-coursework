#include "UnsignedLongLongIO.hpp"
#include <bitset>
#include "DelimiterIO.hpp"

std::istream& tampio::operator>>(std::istream& in, UnsignedLongLongIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  std::string tmp = "";
  in >> DelimeterIO{'0'};
  char c = 0;
  in >> c;
  do
  {
    tmp += c;
  }
  while (in >> c && c != ':' && (c == '0' || c == '1'));
  in.putback(':');
  tmp.erase(0, 1);
  dest.ref = std::bitset< 32 >(tmp).to_ullong();
  return in;
}
