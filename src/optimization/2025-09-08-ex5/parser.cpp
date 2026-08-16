#include <optimization/2025-09-08-ex5/parser.hpp>

#include <fstream>
#include <sstream>
#include <string>

bool LoadParameters(const std::string& path, Parameters*out, std::string*error) {
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
    } else if (tag == "C") {
      row >> out->num_customers;
    } else if (tag == "A") {
      row >> out->min_wait;
    } else if (tag == "B") {
      row >> out->max_wait;
    } else if (tag == "F") {
      row >> out->num_suppliers;
    } else if (tag == "G" || tag == "V") {
      row >> out->budget;
    } else if (tag == "P") {
      row >> out->num_products;
    } else if (tag == "S") {
      row >> out->num_servers;
    } else if (tag == "K") {
      row >> out->max_items;
    }
  }

  if (out->time_step <= 0.0 || out->horizon <= 0.0 || out->simulations <= 0 ||
      out->num_customers <= 0 || out->num_suppliers <= 0 || out->budget <= 0 ||
      out->num_products <= 0 || out->num_servers <= 0) {
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
