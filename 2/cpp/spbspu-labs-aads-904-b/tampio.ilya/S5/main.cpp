#include <fstream>
#include <iostream>
#include <limits>
#include "../common/DictionaryBST.hpp"
#include "../common/ForwardList.hpp"
#include "Logger.hpp"

using namespace tampio;

struct Key_summ
{
  void operator()(const std::pair< const int, std::string > &key_value)
  {
    int result = result_ + key_value.first;
    if (key_value.first >= 0 && result < result_)
    {
      throw std::out_of_range("overflow occured");
    }
    if (key_value.first < 0 && result >= result_)
    {
      throw std::out_of_range("underflow occured");
    }
    result_ += key_value.first;
  }
  int result_ = 0;
};

struct Val_print
{
  void operator()(const std::pair< const int, std::string > &key_value)
  {
    std::cout << ' ' << key_value.second;
  }
};

int main(int argc, char *argv[])
{
  if (argc != 3)
  {
    std::cerr << "Invalid argumments";
    return 1;
  }
  std::ifstream in(argv[2]);
  std::string traversalType(argv[1]);
  if (traversalType != "ascending" && traversalType != "descending" && traversalType != "breadth" )
  {
    std::cerr << "unexpected traversal type\n";
    return 1;
  }

  using Dict = BinarySearchTree< int, std::string >;
  ForwardList< std::string > lexemes;
  Dict dataset;

  try
  {
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
        while (!lexemes.empty())
        {
          int key = std::stoi(lexemes.front());
          lexemes.deleteFront();
          if (lexemes.empty())
          {
            throw std::logic_error("strange");
          }
          std::string value = lexemes.front();
          if (value == "")
          {
            throw std::logic_error("strange");
          }
          lexemes.deleteFront();
          dataset.push(key, value);
        }
      }
    }
    if (dataset.empty())
    {
      Logger::log(Logger::Message::EMPTY, std::cout);
      return 0;
    }

    long sum = 0;

    if (traversalType == "ascending")
    {
      sum = dataset.traverse_lnr(Key_summ()).result_;
    }
    else if (traversalType == "descending")
    {
      sum = dataset.traverse_rnl(Key_summ()).result_;
    }
    else if (traversalType == "breadth")
    {
      sum = dataset.traverse_breadth(Key_summ()).result_;
    }
    std::cout << sum;
  }
  catch (const std::exception &e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }

  if (traversalType == "ascending")
  {
    dataset.traverse_lnr(Val_print());
  }
  else if (traversalType == "descending")
  {
    dataset.traverse_rnl(Val_print());
  }
  else if (traversalType == "breadth")
  {
    dataset.traverse_breadth(Val_print());
  }
  std::cout << '\n';
}
