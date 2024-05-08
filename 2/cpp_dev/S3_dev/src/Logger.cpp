#include "Logger.hpp"

void tampio::Logger::log(std::ostream& os, Message m)
{
  os << "<";
  switch (m)
  {
  case Message::EMPTY:
    os << "EMPTY";
    break;
  case Message::TRUE:
    os << "TRUE";
    break;
  case Message::FALSE:
    os << "FALSE";
    break;
  case Message::INVALID_COMMAND:
    os << "INVALID COMMAND";
    break;
  }
  os << ">\n";
}