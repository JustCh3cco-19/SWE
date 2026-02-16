#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <string>

struct Parameters {
  double T = 0.0;
  double H = 0.0;
  int M = 0;
  int C = 0;
  double A = 0.0;
  double B = 0.0;
  int Q = 0;
  double V = 0.0;
  double W = 0.0;
  int P = 0;
  int S = 0;
  int F = 0;
};

bool ReadParameters(const std::string& path, Parameters& out);

#endif
