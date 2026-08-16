#include <queues-and-services/2025-03-21-ex1/parser.hpp>

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

namespace {

bool ParseNumbers(const std::string& line, std::vector<double>*values) {
  values->clear();
  std::istringstream row(line);
  double value = 0.0;
  while (row >> value) {
    values->push_back(value);
  }
  return !values->empty();
}

}  // namespace

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
  bool area_set = false;
  while (std::getline(input, line)) {
    if (line.empty()) {
      continue;
    }
    std::istringstream row(line);
    std::string tag;
    row >> tag;
    if (tag == "H") {
      double value = 0.0;
      row >> value;
      out->horizon = static_cast<int>(value);
    } else if (tag == "N") {
      row >> out->num_drones;
    } else if (tag == "A") {
      row >> out->alpha;
    } else if (tag == "R") {
      row >> out->radius;
    } else {
      std::vector<double> values;
      if (!ParseNumbers(line, &values)) {
        continue;
      }
      if (values.size() == 6 && !area_set) {
        out->x1 = values[0];
        out->x2 = values[1];
        out->y1 = values[2];
        out->y2 = values[3];
        out->z1 = values[4];
        out->z2 = values[5];
        area_set = true;
      }
    }
  }

  if (out->horizon <= 0 || out->num_drones <= 0 || !area_set) {
    if (error) {
      *error = "Invalid parameters.txt";
    }
    return false;
  }

  return true;
}
