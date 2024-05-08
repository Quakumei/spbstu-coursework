#include <iostream>
#include <fstream>
#include <string>
#include "Stack.hpp"
#include "ExpressionCalculator.h"

int main(int argc, char *argv[])
{
    bool memoryAllocated = false;
    std::istream *is;
    switch (argc)
    {
    case 2:
    {
        std::string filename = argv[1];
        is = new std::ifstream(filename);
        memoryAllocated = true;

        if (is->peek() == EOF && is->eof())
        {
            std::cout << '\n';
            delete is;
            memoryAllocated = false;
            return 0;
        }
        break;
    }
    case 1:
        is = &std::cin;
        break;
    default:
        throw std::logic_error("Filename should be specified as an only argument");
    }

    std::string line;
    Stack<long long> results;

    while (!(is->peek() == EOF || is->eof()))
    {
        std::getline(*is, line);

        if (!line.empty())
        {
            try
            {
                ExpressionCalculator ec(line);
                results.push(ec.solve());
            }
            catch (std::logic_error const &e)
            {
                std::cerr << "Bad expression! ( " << e.what() << ")\n";
                if (memoryAllocated)
                {
                    delete is;
                }
                return -1;
            }
            catch (std::overflow_error const &e)
            {
                std::cerr << "Calculation error! ( " << e.what() << ")\n";
                if (memoryAllocated)
                {
                    delete is;
                }
                return -2;
            }
        }
    }
    if (!results.isEmpty())
    {
        long long res = results.drop();
        std::cout << res;
        while (!results.isEmpty())
        {
            res = results.drop();
            std::cout << ' ' << res;
        }
        std::cout << '\n';
    }
    if (memoryAllocated)
    {
        delete is;
    }
    return 0;
}
