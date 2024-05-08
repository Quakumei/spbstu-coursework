#include <fstream>
#include <iostream>
#include <stdexcept>

#include "dictionary.hpp"
#include "utils.hpp"

int main(int argc, char** argv)
{
  if (argc != 2)
  {
    std::cerr << "File name not found" << std::endl;
    return 42;
  }
  std::ifstream file(argv[1]);
  std::string data;
  gaile::ddict_t db;

  try
  {
    while (getline(file, data))
    {
      std::string name = data.substr(0, data.find(' '));
      data = data.substr(data.find(' ') + 1);
      gaile::dict_t node;

      while (data.find(' ') != std::string::npos)
      {
        std::string key = data.substr(0, data.find(' '));
        data = data.substr(data.find(' ') + 1);

        std::string value = data.substr(0, data.find(' '));
        data = data.substr(data.find(' ') + 1);

        if (key.empty() || value.empty())
        {
          break;
        }
        node[key] = value;
      }
      db[name] = node;
    }

    std::string cmd;
    while (getline(std::cin, data))
    {
      cmd = data.substr(0, data.find(' '));
      data = data.substr(data.find(' ') + 1);

      if (cmd == "print")
      {
        std::string name = data.substr(0, data.find(' '));
        data = data.substr(data.find(' ') + 1);
        if (db.find(name) == db.end())
        {
          std::cout << "<INVALID COMMAND>" << std::endl;
          continue;
        }

        if (db[name].empty())
        {
          std::cout << "<EMPTY>" << std::endl;
          continue;
        } else
        {
          std::cout << name << ' ';
          gaile::print(db[name], std::cout);
        }
      } else
      {
        std::string namenewdb = data.substr(0, data.find(' '));
        data = data.substr(data.find(' ') + 1);

        std::string firstname = data.substr(0, data.find(' '));
        data = data.substr(data.find(' ') + 1);

        std::string secondname = data.substr(0, data.find(' '));
        data = data.substr(data.find(' ') + 1);

        if (db.find(firstname) == db.end() || db.find(secondname) == db.end())
        {
          std::cout << "<INVALID COMMAND>" << std::endl;
          continue;
        }

        gaile::dict_t newdb;
        gaile::dict_t first = db[firstname];
        gaile::dict_t second = db[secondname];

        if (cmd == "complement")
        {
          newdb = gaile::complement(first, second);
        } else if (cmd == "intersect")
        {
          newdb = gaile::intersect(first, second);
        } else if (cmd == "union")
        {
          newdb = gaile::unionDict(first, second);
        } else
        {
          std::cout << "<INVALID COMMAND>" << std::endl;
          continue;
        }
        db[namenewdb] = newdb;
      }
    }
  } catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
    return 1;
  }
}
