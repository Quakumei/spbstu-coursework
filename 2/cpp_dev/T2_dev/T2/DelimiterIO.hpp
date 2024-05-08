#ifndef DELIMITER_IO
#define DELIMITER_IO

#include <istream>

namespace tampio
{
  struct DelimeterIO
  {
    char exp;
  };
  std::istream& operator>>(std::istream& in, DelimeterIO&& dest);
}

#endif
