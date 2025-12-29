#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <vector>

#include "swe_utils.h"

struct Transition {
  int to;
  double prob;
  double cost;
};

int main() {
  std::ifstream input("parameters.txt");
  if (!input) {
    std::cerr << "Cannot open parameters.txt\n";
    return 1;
  }

  std::string line;
  int num_states = -1;
  if (std::getline(input, line)) {
    std::istringstream header(line);
    std::string tag;
    header >> tag >> num_states;
    if (tag != "N" || num_states <= 0) {
      std::cerr << "Invalid header in parameters.txt\n";
      return 1;
    }
  } else {
    std::cerr << "Empty parameters.txt\n";
    return 1;
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

  const int simulations = 1000;
  std::mt19937 rng = swe::MakeRng();
  std::uniform_real_distribution<double> dist(0.0, 1.0);

  double total_cost = 0.0;
  for (int sim = 0; sim < simulations; ++sim) {
    int state = 0;
    double cost = 0.0;
    int safety = 0;
    while (state != num_states - 1) {
      const auto& outs = transitions[state];
      if (outs.empty()) {
        break;
      }
      double r = dist(rng);
      double acc = 0.0;
      int next_state = outs.back().to;
      double step_cost = outs.back().cost;
      for (const auto& t : outs) {
        acc += t.prob;
        if (r <= acc) {
          next_state = t.to;
          step_cost = t.cost;
          break;
        }
      }
      cost += step_cost;
      state = next_state;
      if (++safety > 1000000) {
        break;
      }
    }
    total_cost += cost;
  }

  double average = total_cost / simulations;

  std::ofstream output("results.txt");
  if (!output) {
    std::cerr << "Cannot open results.txt\n";
    return 1;
  }

  std::string root_name = swe::RootNameFromCwd();

  output << root_name << "\n";
  output << "C " << average << "\n";
  return 0;
}
