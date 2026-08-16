#include <probability-and-statistics/2025-02-05-ex5/parser.hpp>

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

bool LoadParameters(const std::string& path, Parameters*out, std::string*error) {
  if (!out) {
    return false;
  }

  *out = Parameters{};

  std::ifstream input(path);
  if (!input) {
    if (error) {
      *error = "Cannot open parameters.txt";
    }
    return false;
  }

  std::string line;
  std::vector<double> times;
  while (std::getline(input, line)) {
    if (line.empty()) {
      continue;
    }
    std::istringstream row(line);
    std::string tag;
    row >> tag;
    if (tag == "L") {
      row >> out->threshold;
      continue;
    }
    row.clear();
    row.str(line);
    int i = -1;
    int j = -1;
    double p = 0.0;
    if (row >> i) {
      if (row >> j >> p) {
        if (i >= 0 && i < 3 && j >= 0 && j < 3) {
          out->probs[static_cast<std::size_t>(i)][static_cast<std::size_t>(j)] = p;
        }
        continue;
      }
    }
    row.clear();
    row.str(line);
    double value = 0.0;
    if (row >> value) {
      times.push_back(value);
    }
  }

  if (times.size() >= 2) {
    out->t1 = times[0];
    out->t2 = times[1];
  }

  return true;
}
