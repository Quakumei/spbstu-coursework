#include "Command.hpp"
void tampio::Command::print(dictOfDict dictionariesOfDict, std::string word)
{
  if (!dictionariesOfDict.boolFind(word))
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
  if (!dictionariesOfDict.find(word)->second.isEmpty())
  {
    std::cout << word << " ";
    dictionariesOfDict.find(word)->second.print();
  } else
  {
    std::cout << "<EMPTY>\n";
  }
}

dict tampio::Command::complement(dictOfDict dictionariesOfDict, std::string firstDataset, std::string secondDataset)
{
  dict dictionariesFirstOfValues = dictionariesOfDict.find(firstDataset)->second;
  dict dictionariesSecondOfValues = dictionariesOfDict.find(secondDataset)->second;
  for (dict::iterator_t iter = dictionariesSecondOfValues.cbegin(); iter != dictionariesSecondOfValues.cend(); iter++)
  {
    if (dictionariesFirstOfValues.boolFind(iter->first))
    {
      dictionariesFirstOfValues.drop(iter->first);
    }
  }
  return dictionariesFirstOfValues;
}

dict tampio::Command::intersect(dictOfDict dictionariesOfDict, std::string firstDataset, std::string secondDataset)
{
  tampio::Dictionary< std::string, std::string > needDict;
  for (dict::iterator_t iter = dictionariesOfDict.find(firstDataset)->second.cbegin();
       iter != dictionariesOfDict.find(firstDataset)->second.cend();
       iter++)
  {
    if (dictionariesOfDict.find(secondDataset)->second.boolFind(iter->first))
    {
      needDict.push(iter->first, iter->second);
    }
  }
  return needDict;
}

dict tampio::Command::unionDict(dictOfDict dictionariesOfDict, std::string firstDataset, std::string secondDataset)
{
  tampio::Dictionary< std::string, std::string > secondForDataset = dictionariesOfDict.find(secondDataset)->second;
  tampio::Dictionary< std::string, std::string > firstForDataset = dictionariesOfDict.find(firstDataset)->second;
  for (Dictionary< std::string, std::string >::iterator_t current = firstForDataset.cbegin();
       current != firstForDataset.cend();
       current++)
  {
    if (secondForDataset.boolFind(current->first))
    {
      secondForDataset.drop(current->first);
    }
  }
  for (Dictionary< std::string, std::string >::iterator_t current = secondForDataset.cbegin();
       current != secondForDataset.cend();
       current++)
  {
    firstForDataset.push(current->first, current->second);
  }
  return firstForDataset;
}