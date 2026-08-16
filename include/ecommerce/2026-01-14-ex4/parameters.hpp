#ifndef EXAMPLES_ECOMMERCE_2026_01_14_EX4_PARAMETERS_HPP_
#define EXAMPLES_ECOMMERCE_2026_01_14_EX4_PARAMETERS_HPP_

#include <string>

struct Parameters {
  double T = 0.0;
  double H = 0.0;
  int M = 0;
  int C = 0;
  double A = 0.0;
  double B = 0.0;
  int G = 0;
  double V = 0.0;
  double W = 0.0;
  int Q = 0;
  int P = 0;
  int S = 0;
  double a = 0.0;
  double b = 0.0;
};

bool ReadParameters(const std::string& path, Parameters& out);

#endif
