#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <string>

#include "mocc/mocc.hpp"

struct Parameters {
  real_t T = 0.0;
  real_t H = 0.0;
  real_t L = 0.0;
  real_t V = 0.0;
  real_t A = 0.0;
  real_t D = 0.0;
  real_t R = 0.0;
  int M = 0;
  int N = 0;
};

bool ReadParameters(const std::string& path, Parameters& out);

#endif
