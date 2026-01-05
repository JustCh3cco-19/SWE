#pragma once

#include <string>

struct Parameters {
  double time_step = 0.0;
  double horizon = 0.0;
  int simulations = 0;
  int num_customers = 0;
  double min_wait = 0.0;
  double max_wait = 0.0;
  int num_suppliers = 0;
  double min_supply = 0.0;
  double max_supply = 0.0;
  int num_products = 0;
  int num_servers = 0;
  int max_items = 0;
};

bool LoadParameters(const std::string& path, Parameters* out, std::string* error);
