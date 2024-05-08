#ifndef STRING_IO
#define STRING_IO

#include <istream>

namespace tampio
{
  struct StringIO
  {
    std::string& ref;
  };
  std::istream& operator>>(std::istream& in, StringIO&& dest);
}

#endif
