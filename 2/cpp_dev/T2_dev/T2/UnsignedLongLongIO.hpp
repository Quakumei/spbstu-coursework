#ifndef UNSIGNEDLONGLONG_IO
#define UNSIGNEDLONGLONG_IO

#include <istream>

namespace tampio
{
  struct UnsignedLongLongIO
  {
    unsigned long long& ref;
  };
  std::istream& operator>>(std::istream& in, UnsignedLongLongIO&& dest);
}

#endif
