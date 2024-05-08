#include <fstream>
#include <iostream>

#include "ExpressionCalculator.h"
#include "Stack.hpp"

using namespace tampio;

int main(int argc, char *argv[]) {
  std::ifstream ifs;
  if (argc >= 2) {
    ifs.open(argv[1]);

    if (!ifs.is_open()) {
      std::cerr << "Error when opening file.\n";
      return 1;
    }
  }
  std::istream &is = (argc < 2) ? std::cin : ifs;

  Stack<long long> results;
  try {
    std::string line = "";
    while (getline(is, line)) {
      if (line.empty()) {
        continue;
      }

      ExpressionCalculator ar(line);
      results.push(ar.solve());
    }
  } catch (const std::exception &e) {
    std::cerr << "[Error] : " << e.what() << '\n';
    return 2;
  }

  while (!results.isEmpty()) {
    std::cout << results.peek();
    results.rm_back();

    if (!results.isEmpty()) {
      std::cout << ' ';
    }
  }
  std::cout << '\n';
  return 0;
}
