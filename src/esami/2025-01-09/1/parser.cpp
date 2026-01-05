#include "parser.hpp"

#include <fstream>
#include <sstream>
#include <string>
#include <utility>

bool LoadParameters(const std::string& path, MdpData* out, std::string* error) {
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
  int num_states = -1;
  if (std::getline(input, line)) {
    std::istringstream header(line);
    std::string tag;
    header >> tag >> num_states;
    if (tag != "N" || num_states <= 0) {
      if (error) {
        *error = "Invalid header in parameters.txt";
      }
      return false;
    }
  } else {
    if (error) {
      *error = "Empty parameters.txt";
    }
    return false;
  }

  std::vector<std::vector<Transition>> transitions(num_states);
  while (std::getline(input, line)) {
    if (line.empty()) {
      continue;
    }
    std::istringstream row(line);
    std::string tag;
    row >> tag;
    if (tag != "A") {
      continue;
    }
    int from = -1;
    int to = -1;
    double prob = 0.0;
    double cost = 0.0;
    if (!(row >> from >> to >> prob >> cost)) {
      continue;
    }
    if (from < 0 || from >= num_states) {
      continue;
    }
    transitions[from].push_back(Transition{to, prob, cost});
  }

  out->num_states = num_states;
  out->transitions = std::move(transitions);
  return true;
}
