#pragma once

#include <string>
#include <vector>

struct Transition {
  int to;
  double prob;
  double cost;
};

struct MdpData {
  int num_states = 0;
  std::vector<std::vector<Transition>> transitions;
};

struct Parameters {
  double cost_limit = 0.0;
  MdpData mdp;
};

bool LoadParameters(const std::string& path, Parameters* out, std::string* error);
