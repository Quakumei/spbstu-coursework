#include "Logger.hpp"

void tampio::Logger::log(const Message& msg, std::ostream& os){
    os << "<";
    switch (msg){
        case Message::INVALID_COMMAND:
            os << "INVALID COMMAND";
            break;
        case Message::EMPTY:
            os << "EMPTY";
            break;
    }
    os << ">\n";
}
