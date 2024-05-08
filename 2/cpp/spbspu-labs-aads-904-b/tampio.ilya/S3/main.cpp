#include <cctype>
#include <fstream>
#include <iostream>
#include "BidirectionalList.hpp"
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

  using Dict = Dictionary< std::string, tampio::BidirectionalList< long > >;
  ForwardList< std::string > lexemes;
  Dict lists;
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
      std::string listName = lexemes.front();
      lexemes.deleteFront();
      BidirectionalList< long > list;
      while (!lexemes.empty())
      {
        std::string value = lexemes.front();
        lexemes.deleteFront();
        list.pushBack(std::stol(value));
      }
      lists.push(listName, list);
    }
  }
  while (!std::cin.eof())
  {
    try
    {
      int argcount = -1;
      ForwardList< std::string > commandLine;
      std::string line = "";
      while (line == "")
      {
        std::getline(std::cin, line);
        if (std::cin.eof())
        {
          return 0;
        }
      }
      if (line != "\0")
      {
        line += ' ';
        std::string temp = "";
        for (size_t i = 0; i < line.size(); i++)
        {
          if (line[i] == ' ')
          {
            commandLine.pushBack(temp);
            argcount++;
            temp = "";
          }
          else
          {
            temp += line[i];
          }
        }
      }

      std::string command = "";
      command = commandLine.front();
      commandLine.deleteFront();
      if (command == "print")
      {
        if (argcount != 1)
        {
          throw std::logic_error("bad argcount");
        }
        std::string name;
        name = commandLine.front();
        commandLine.deleteFront();
        BidirectionalList< long > example = lists.get(name);
        print(example, name, std::cout);
      }
      else if (command == "replace")
      {
        if (argcount != 3)
        {
          throw std::logic_error("bad argcount");
        }
        std::string name, left, right;
        name = commandLine.front();
        commandLine.deleteFront();
        left = commandLine.front();
        commandLine.deleteFront();
        right = commandLine.front();
        commandLine.deleteFront();
        if (std::isalpha(right[0]))
        {
          replace(lists.getRef(name), std::stoll(left), lists.get(right));
        }
        else
        {
          replace(lists.getRef(name), std::stoll(left), std::stoll(right));
        }
      }
      else if (command == "remove")
      {
        if (argcount != 2)
        {
          throw std::logic_error("bad argcount");
        }
        std::string name, left;
        name = commandLine.front();
        commandLine.deleteFront();
        left = commandLine.front();
        commandLine.deleteFront();
        if (std::isalpha(left[0]))
        {
          removeElems(lists.getRef(name), lists.get(left));
        }
        else
        {
          removeElems(lists.getRef(name), std::stoll(left));
        }
      }
      else if (command == "concat")
      {
        if (argcount < 3)
        {
          throw std::logic_error("bad argcount");
        }
        std::string name;
        name = commandLine.front();
        commandLine.deleteFront();
        lists.push(name, BidirectionalList< long >());

        while (!commandLine.empty())
        {
          concat(lists.getRef(name), lists.get(commandLine.front()));
          commandLine.deleteFront();
        }
      }
      else if (command == "equal")
      {
        if (argcount < 2)
        {
          throw std::logic_error("bad argcount");
        }

        std::string name;
        name = commandLine.front();
        commandLine.deleteFront();

        std::string other;
        bool flag = true;
        while (!commandLine.empty())
        {
          other = commandLine.front();
          commandLine.deleteFront();
          if (!equal(lists.getRef(name), lists.get(other)))
          {
            flag = false;
            break;
          }
        }
        std::cout << ((flag) ? "<TRUE>" : "<FALSE>") << '\n';
      }
      else if (!std::cin.eof())
      {
        throw std::logic_error("unknown command");
      }
    }
    catch (const std::exception &e)
    {
      std::cout << "<INVALID COMMAND>\n";
    }
  }
}
