#ifndef EXPRESSIONCALULATOR_H
#define EXPRESSIONCALULATOR_H

#include <string>
#include "Queue.hpp"

namespace tampio
{
  class ExpressionCalculator
  {
  public:
    ExpressionCalculator(const std::string &expression);
    long long solve() const;

  private:
    enum Priority : int
    {
      PRIORITY_PARENTHESIS,
      PRIORITY_ADDITION,
      PRIORITY_MULTIPLICATION
    };
    const std::string OPERATORS_ = "-+/*%";
    Queue< std::string > lexemes_;
    Queue< std::string > postfixForm(Queue< std::string >) const;
    static Priority order(const char &);
    static bool isHigher(const char &, const char &);
  };
}

#endif

