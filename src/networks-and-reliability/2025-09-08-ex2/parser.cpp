#include <networks-and-reliability/2025-09-08-ex2/parser.hpp>

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
    } else if (tag == "N") {
      row >> out->num_uav;
    } else if (tag == "L") {
      row >> out->L;
    } else if (tag == "V") {
      row >> out->V;
    } else if (tag == "A") {
      row >> out->A;
    } else if (tag == "D") {
      row >> out->D;
    }
  }

  if (out->time_step <= 0.0 || out->horizon <= 0.0 || out->simulations <= 0 ||
      out->num_uav <= 0 || out->L <= 0.0 || out->V <= 0.0 || out->A <= 0.0 ||
      out->D <= 0.0) {
    if (error) {
      *error = "Invalid parameters.txt";
    }
    return false;
  }

  return true;
}
