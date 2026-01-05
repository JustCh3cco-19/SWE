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
    if (tag == "T") {
      row >> out->time_step;
    } else if (tag == "H") {
      row >> out->horizon;
    } else if (tag == "M") {
      row >> out->simulations;
    } else if (tag == "A") {
      row >> out->min_wait;
    } else if (tag == "B") {
      double first = 0.0;
      if (row >> first) {
        double second = 0.0;
        if (row >> second) {
          out->budget = static_cast<int>(first);
          out->cost_g = second;
        } else {
          out->max_wait = first;
        }
      }
    } else if (tag == "V") {
      row >> out->min_server;
    } else if (tag == "W" || tag == "Q") {
      row >> out->max_server;
    } else if (tag == "P") {
      row >> out->num_products;
    } else if (tag == "K") {
      row >> out->max_items;
    } else if (tag == "G") {
      row >> out->cost_g;
    } else if (tag == "BUDGET") {
      row >> out->budget;
    }
  }

  if (out->time_step <= 0.0 || out->horizon <= 0.0 || out->simulations <= 0 ||
      out->num_products <= 0 || out->max_items < 0 || out->budget <= 0) {
    if (error) {
      *error = "Invalid parameters.txt";
    }
    return false;
  }
  if (out->min_wait > out->max_wait || out->min_server > out->max_server) {
    if (error) {
      *error = "Invalid wait interval";
    }
    return false;
  }

  return true;
}
