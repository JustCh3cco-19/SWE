#include <networks-and-reliability/2025-06-12-ex1/parser.hpp>

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
    if (tag == "H") {
      row >> out->horizon;
    } else if (tag == "N") {
      row >> out->num_vehicles;
    } else if (tag == "V") {
      row >> out->speed;
    } else if (tag == "T") {
      row >> out->time_step;
    }
  }

  if (out->horizon <= 0.0 || out->num_vehicles <= 0 || out->time_step <= 0.0) {
    if (error) {
      *error = "Invalid parameters.txt";
    }
    return false;
  }

  return true;
}
