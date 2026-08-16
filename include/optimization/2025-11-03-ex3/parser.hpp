#pragma once

#include <string>
#include <vector>

struct Transition {
  int to = 0;
  double prob = 0.0;
  double cost = 0.0;
};

struct Parameters {
  int num_states = 0;
  int simulations = 0;
  int budget = 0;
  double k_cost = 0.0;
  double cost_self = 0.0;
  double cost_next = 0.0;
  std::vector<std::vector<Transition> > transitions;
};

bool LoadParameters(const std::string& path, Parameters*out, std::string*error);
