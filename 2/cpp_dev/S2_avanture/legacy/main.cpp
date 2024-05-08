#include <fstream>
#include <iostream>

#include "Command.hpp"
#include "Dictionary.hpp"
#include "ForwardList.hpp"

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    std::cerr << "Error input file";
    return 1;
  }
  using dictOfDict = tampio::Dictionary< std::string, tampio::Dictionary< std::string, std::string > >;
  std::ifstream in(argv[1]);
  std::cout << "debug1\n";
  tampio::ForwardList< std::string > words;
  std::cout << "debug1\n";
  dictOfDict dictionariesOfDict;
  std::cout << "debug1\n";
  while (!in.eof())
  {
    std::string line = "";
    getline(in, line);
    if (line != "\0")
    {
      line += ' ';
      std::string temp = "";
      for (size_t i = 0; i < line.size(); i++)
      {
        if (line[i] == ' ')
        {
          words.pushTail(temp);
          temp = "";
        } else
        {
          temp += line[i];
        }
      }
      std::string nameOfDict = words.top();
      words.rmFront();
      tampio::Dictionary< std::string, std::string > dictionariesOfValues;
      while (!words.isEmpty())
      {
        std::string key = words.top();
        words.rmFront();
        std::string value = words.top();
        words.rmFront();
        dictionariesOfValues.push(key, value);
      }
      dictionariesOfDict.push(nameOfDict, dictionariesOfValues);
    }
  }
  std::string commandLine = "";
  while (std::getline(std::cin, commandLine))
  {
    try
    {
      if (commandLine != "\0")
      {
        commandLine += ' ';
        std::string command = "";
        for (size_t i = 0; i < commandLine.size(); i++)
        {
          if (commandLine[i] == ' ')
          {
            words.pushTail(command);
            command = "";
          } else
          {
            command += commandLine[i];
          }
        }
        tampio::Command forCommands;
        if (words.top() == "print")
        {
          words.rmFront();
          forCommands.print(dictionariesOfDict, words.top());
          words.rmFront();
        } else if (words.top() == "complement")
        {
          words.rmFront();
          std::string newDataset = words.top();
          words.rmFront();
          std::string firstDataset = words.top();
          words.rmFront();
          std::string secondDataset = words.top();
          words.rmFront();
          if (!dictionariesOfDict.boolFind(firstDataset) || !dictionariesOfDict.boolFind(secondDataset))
          {
            throw std::logic_error("<INVALID COMMAND>");
          } else if (dictionariesOfDict.boolFind(newDataset))
          {
            dictionariesOfDict.find(newDataset)->second =
                forCommands.complement(dictionariesOfDict, firstDataset, secondDataset);
          } else
          {
            dictionariesOfDict.push(newDataset,
                forCommands.complement(dictionariesOfDict, firstDataset, secondDataset));
          }
        } else if (words.top() == "intersect")
        {
          words.rmFront();
          std::string newDataset = words.top();
          words.rmFront();
          std::string firstDataset = words.top();
          words.rmFront();
          std::string secondDataset = words.top();
          words.rmFront();
          if (!dictionariesOfDict.boolFind(firstDataset) || !dictionariesOfDict.boolFind(secondDataset))
          {
            throw std::logic_error("<INVALID COMMAND>");
          } else if (dictionariesOfDict.boolFind(newDataset))
          {
            dictionariesOfDict.find(newDataset)->second =
                forCommands.intersect(dictionariesOfDict, firstDataset, secondDataset);
          } else
          {
            dictionariesOfDict.push(newDataset, forCommands.intersect(dictionariesOfDict, firstDataset, secondDataset));
          }
        } else if (words.top() == "union")
        {
          words.rmFront();
          std::string newDataset = words.top();
          words.rmFront();
          std::string firstDataset = words.top();
          words.rmFront();
          std::string secondDataset = words.top();
          words.rmFront();
          if (!dictionariesOfDict.boolFind(firstDataset) || !dictionariesOfDict.boolFind(secondDataset))
          {
            throw std::logic_error("<INVALID COMMAND>");
          } else if (dictionariesOfDict.boolFind(newDataset))
          {
            dictionariesOfDict.find(newDataset)->second =
                forCommands.unionDict(dictionariesOfDict, firstDataset, secondDataset);
          } else
          {
            dictionariesOfDict.push(newDataset, forCommands.unionDict(dictionariesOfDict, firstDataset, secondDataset));
          }
        } else
        {
          std::cout << "<INVALID COMMAND>\n";
        }
      }
    } catch (const std::exception &ex)
    {
      std::cout << ex.what() << "\n";
    }
  }
}