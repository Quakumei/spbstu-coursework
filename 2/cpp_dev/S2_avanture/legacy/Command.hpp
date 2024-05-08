#ifndef COMMAND_H
#define COMMAND_H
#include "Dictionary.hpp"
#include "ForwardList.hpp"
using dict = tampio::Dictionary< std::string, std::string >;
using dictOfDict = tampio::Dictionary< std::string, tampio::Dictionary< std::string, std::string > >;
namespace tampio
{
  class Command
  {
  public:
    void print(dictOfDict dictionariesOfDict, std::string word);
    dict complement(dictOfDict dictionariesOfDict, std::string firstDataset, std::string secondDataset);
    dict intersect(dictOfDict dictionariesOfDict, std::string firstDataset, std::string secondDataset);
    dict unionDict(dictOfDict dictionariesOfDict, std::string firstDataset, std::string secondDataset);
  };
} // namespace tampio
#endif