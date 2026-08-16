#pragma once

#include <string>
#include <vector>

struct Parameters {
  int horizon = 0;
  int num_servers = 0;
  int num_products = 0;
  double alpha = 0.0;
  std::vector<double> customer_probs;
  std::vector<double> supplier_probs;
};

bool LoadParameters(const std::string& path, Parameters*out, std::string*error);
