#ifndef TOKENIZE_H
#define TOKENIZE_H

#include <string>
#include "Queue.hpp"

namespace tampio {
    Queue< std::string > convertToLexemes(const std::string &expr);
}

#endif

