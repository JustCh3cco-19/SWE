#pragma once

#include <string>

struct Parameters {
  int simulations = 0;
  double horizon = 0.0;
  int num_products = 0;
  double min_wait = 0.0;
  double max_wait = 0.0;
  double time_step = 0.0;
  int num_servers = 0;
  int max_items = 0;
  double prob = 0.0;
  double dispatcher_time = 0.0;
  double server_time = 0.0;
};

bool LoadParameters(const std::string& path, Parameters* out, std::string* error);
