#ifndef LABEL_IO
#define LABEL_IO

#include <istream>

namespace tampio
{
  struct LabelIO
  {
    std::string exp;
  };
  std::istream& operator>>(std::istream& in, LabelIO&& dest);
}

#endif
