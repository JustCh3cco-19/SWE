#include "parser.hpp"

#include <fstream>
#include <sstream>
#include <string>
#include <utility>

namespace {

struct EdgeRecord {
  int from;
  int to;
  double prob;
  double cost;
};

}  // namespace

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
  double cost_limit = 0.0;
  if (std::getline(input, line)) {
    std::istringstream header(line);
    std::string tag;
    header >> tag >> cost_limit;
    if (tag != "C") {
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

  int num_states = -1;
  std::vector<EdgeRecord> edges;
  while (std::getline(input, line)) {
    if (line.empty()) {
      continue;
    }
    std::istringstream row(line);
    std::string tag;
    row >> tag;
    if (tag == "N") {
      row >> num_states;
      continue;
    }
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
    edges.push_back(EdgeRecord{from, to, prob, cost});
  }

  if (num_states <= 0) {
    int max_state = -1;
    for (const auto& e : edges) {
      if (e.from > max_state) {
        max_state = e.from;
      }
      if (e.to > max_state) {
        max_state = e.to;
      }
    }
    if (max_state < 0) {
      if (error) {
        *error = "No states found in parameters.txt";
      }
      return false;
    }
    num_states = max_state + 1;
  }

  std::vector<std::vector<Transition>> transitions(num_states);
  for (const auto& e : edges) {
    if (e.from < 0 || e.from >= num_states) {
      continue;
    }
    transitions[e.from].push_back(Transition{e.to, e.prob, e.cost});
  }

  out->cost_limit = cost_limit;
  out->mdp.num_states = num_states;
  out->mdp.transitions = std::move(transitions);
  return true;
}
