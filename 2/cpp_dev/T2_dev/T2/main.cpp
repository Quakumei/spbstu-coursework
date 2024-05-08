#include <algorithm>
#include <iostream>
#include <iterator>
#include <limits>
#include <vector>
#include "DataStruct.hpp"

using namespace tampio;

int main()
{
  std::vector< DataStruct > data;
  while (!std::cin.eof())
  {
    if ((std::cin.rdstate() & std::ios::failbit) != 0)
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    std::copy(std::istream_iterator< DataStruct >(std::cin),
              std::istream_iterator< DataStruct >(),
              std::back_inserter(data));
  }
  std::sort(data.begin(), data.end());
  std::copy(std::begin(data), std::end(data), std::ostream_iterator< DataStruct >(std::cout, "\n"));
}
