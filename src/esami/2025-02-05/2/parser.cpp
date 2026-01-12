#include "parser.hpp"

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

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
  int expected_points = -1;
  bool area_set = false;

  while (std::getline(input, line)) {
    if (line.empty()) {
      continue;
    }
    std::istringstream row(line);
    std::string tag;
    row >> tag;
    if (tag == "C") {
      row >> out->coverage_limit;
    } else if (tag == "H") {
      double value = 0.0;
      row >> value;
      out->horizon = static_cast<int>(value);
    } else if (tag == "N") {
      row >> out->num_drones;
    } else if (tag == "M") {
      row >> expected_points;
    } else {
      std::vector<double> values;
      if (!mocc_utils::ParseNumbers(line, &values)) {
        continue;
      }
      if (values.size() == 4 && !area_set) {
        out->x1 = values[0];
        out->x2 = values[1];
        out->y1 = values[2];
        out->y2 = values[3];
        area_set = true;
      } else if (values.size() == 2) {
        out->points.push_back(mocc_utils::Point{values[0], values[1]});
      }
    }
  }

  if (out->horizon <= 0 || out->num_drones <= 0 || !area_set) {
    if (error) {
      *error = "Invalid parameters.txt";
    }
    return false;
  }
  if (expected_points >= 0 && expected_points != static_cast<int>(out->points.size())) {
    if (error) {
      *error = "Mismatch between M and points list";
    }
    return false;
  }

  return true;
}
