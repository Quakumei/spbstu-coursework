#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <ostream>

namespace tampio
{
  struct Logger
  {
    enum Message
    {
      TRUE,
      FALSE,
      INVALID_COMMAND,
      EMPTY,
    };
    static void log(std::ostream& os, Message m);
  };
}

#endif