#pragma once

#include <string>

#include "exam_utils.hpp"

struct Parameters {
  double cost_limit = 0.0;
  mocc_utils::MdpData mdp;
};

bool LoadParameters(const std::string& path, Parameters* out, std::string* error);
