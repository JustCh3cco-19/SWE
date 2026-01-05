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

bool LoadParameters(const std::string& path, MdpData* out, std::string* error);
