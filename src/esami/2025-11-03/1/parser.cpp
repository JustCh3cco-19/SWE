#include "parser.hpp"

#include <fstream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

namespace {

struct Edge {
  int from = 0;
  int to = 0;
  double prob = 0.0;
  double cost = 0.0;
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
  std::vector<Edge> edges;
  int num_states = -1;
  int simulations = -1;

  while (std::getline(input, line)) {
    if (line.empty()) {
      continue;
    }
    std::istringstream row(line);
    std::string tag;
    row >> tag;
    if (tag == "N") {
      row >> num_states;
    } else if (tag == "M") {
      row >> simulations;
    } else if (tag == "A") {
      Edge edge;
      row >> edge.from >> edge.to >> edge.prob >> edge.cost;
      edges.push_back(edge);
    }
  }

  if (num_states <= 0) {
    int max_state = -1;
    for (const auto& edge : edges) {
      max_state = std::max(max_state, std::max(edge.from, edge.to));
    }
    if (max_state >= 0) {
      num_states = max_state + 1;
    }
  }

  if (num_states <= 0 || simulations <= 0) {
    if (error) {
      *error = "Invalid parameters.txt";
    }
    return false;
  }

  std::vector<std::vector<Transition>> transitions(num_states);
  for (const auto& edge : edges) {
    if (edge.from < 0 || edge.from >= num_states) {
      continue;
    }
    transitions[edge.from].push_back(Transition{edge.to, edge.prob, edge.cost});
  }

  out->num_states = num_states;
  out->simulations = simulations;
  out->transitions = std::move(transitions);
  return true;
}
