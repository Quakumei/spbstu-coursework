#include "StringIO.hpp"
#include "DelimiterIO.hpp"

std::istream& tampio::operator>>(std::istream& in, StringIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return std::getline(in >> DelimeterIO{'"'}, dest.ref, '"');
}
