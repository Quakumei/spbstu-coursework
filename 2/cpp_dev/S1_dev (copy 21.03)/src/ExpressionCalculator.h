#ifndef EXPRESSIONCALULATOR_H
#define EXPRESSIONCALULATOR_H

#include <string>
#include "Queue.hpp"

class ExpressionCalculator{
    public:
        ExpressionCalculator(const std::string&);
        long long solve() const;
        Queue<std::string> postfixForm(Queue<std::string>) const;

    private:
        void exprToLexemes(const std::string&);
        Queue<std::string> lexemes_;
        static int order(const char &);
        static bool isHigher(const char &, const char &);
};

#endif
