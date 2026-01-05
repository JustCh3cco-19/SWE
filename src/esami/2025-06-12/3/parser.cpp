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
    if (tag == "H") {
      row >> out->horizon;
    } else if (tag == "N") {
      row >> out->num_products;
    } else if (tag == "A") {
      row >> out->min_wait;
    } else if (tag == "B") {
      row >> out->max_wait;
    } else if (tag == "T") {
      row >> out->time_step;
    }
  }

  if (out->horizon <= 0.0 || out->num_products <= 0 || out->time_step <= 0.0) {
    if (error) {
      *error = "Invalid parameters.txt";
    }
    return false;
  }
  if (out->min_wait > out->max_wait) {
    if (error) {
      *error = "Invalid wait interval";
    }
    return false;
  }

  return true;
}
