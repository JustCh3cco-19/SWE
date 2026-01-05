#include "parser.hpp"

#include <fstream>
#include <sstream>
#include <string>

bool LoadParameters(const std::string& path, Parameters* out, std::string* error) {
  if (!out) {
    return false;
  }

  std::ifstream input(path);
  if (!input) {
    if (error) {
      *error = "Cannot open parameters.txt";
    }
    return false;
  }

  std::string line;
  while (std::getline(input, line)) {
    if (line.empty()) {
      continue;
    }
    std::istringstream row(line);
    std::string tag;
    row >> tag;
    if (tag == "Avg") {
      row >> out->avg;
    } else if (tag == "StdDev") {
      row >> out->stddev;
    }
  }

  return true;
}
