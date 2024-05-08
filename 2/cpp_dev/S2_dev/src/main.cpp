#include <fstream>
#include <iostream>
#include <limits>
#include "Dictionary.hpp"
#include "utility.hpp"

using namespace tampio;

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    std::cerr << "No input file specified";
    return 1;
  }
  std::ifstream in(argv[1]);

  using Dict = Dictionary< std::string, std::string >;
  using DictOfDict = Dictionary< std::string, Dict >;
  ForwardList< std::string > lexemes;
  DictOfDict datasets;
  while (!in.eof())
  {
    std::string line = "";
    std::getline(in, line);
    if (line != "\0")
    {
      line += ' ';
      std::string temp = "";
      for (size_t i = 0; i < line.size(); i++)
      {
        if (line[i] == ' ')
        {
          lexemes.pushBack(temp);
          temp = "";
        }
        else
        {
          temp += line[i];
        }
      }
      std::string datasetName = lexemes.front();
      lexemes.deleteFront();
      Dict dataset;
      while (!lexemes.empty())
      {
        std::string key = lexemes.front();
        lexemes.deleteFront();
        std::string value = lexemes.front();
        lexemes.deleteFront();
        dataset.push(key, value);
      }
      datasets.push(datasetName, dataset);
    }
  }
  while (!std::cin.eof())
  {
    try
    {

      std::string command = "";
      std::cin >> command;
      if (command == "print")
      {
        std::string name;
        std::cin >> name;
        Dict example = datasets.get(name);
        print(example, name, std::cout);
      }
      else if (command == "complement")
      {
        std::string name, left, right;
        std::cin >> name >> left >> right;
        datasets.push(name, complement(datasets.get(left), datasets.get(right)));
      }
      else if (command == "intersect")
      {
        std::string name, left, right;
        std::cin >> name >> left >> right;
        datasets.push(name, intersect(datasets.get(left), datasets.get(right)));
      }
      else if (command == "union")
      {
        std::string name, left, right;
        std::cin >> name >> left >> right;
        datasets.push(name, unionDict(datasets.get(left), datasets.get(right)));
      }
      else if (!std::cin.eof())
      {
        throw std::logic_error("unknown command");
      }
    }
    catch (const std::exception &)
    {
      std::cout << "<INVALID COMMAND>\n";
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
}
