#ifndef EXAMPLES_NETWORKS_AND_RELIABILITY_2026_01_14_EX2_PARAMETERS_HPP_
#define EXAMPLES_NETWORKS_AND_RELIABILITY_2026_01_14_EX2_PARAMETERS_HPP_

#include <string>

struct Parameters {
  double T = 0.0;
  double H = 0.0;
  double L = 0.0;
  double V = 0.0;
  double D = 0.0;
  double R = 0.0;
  int M = 0;
  int N = 0;
};

bool ReadParameters(const std::string& path, Parameters& out);

#endif
