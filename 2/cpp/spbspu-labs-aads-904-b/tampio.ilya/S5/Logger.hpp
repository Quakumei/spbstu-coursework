#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <ostream>

namespace tampio
{
  class Logger
  {
  public:
    enum Message
    {
      INVALID_COMMAND,
      EMPTY,
    };
    static void log(const Message&, std::ostream&);
  };
}

#endif
