#include "LongLongIO.hpp"

std::istream& tampio::operator>>(std::istream& in, LongLongIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  long long number = 0;
  char l1 = '0', l2 = '0';
  in >> number;
  in >> l1 >> l2;
  dest.ref = number;
  if ((l1 != l2) && !(l1 == 'l' || l1 == 'L'))
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}
