#ifndef LONGLONG_IO
#define LONGLONG_IO

#include <istream>

namespace tampio
{
  struct LongLongIO
  {
    long long& ref;
  };
  std::istream& operator>>(std::istream& in, LongLongIO&& dest);
}

#endif
