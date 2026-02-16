#pragma once

#include <random>
#include <vector>

using urng_t = std::default_random_engine;
using real_t = double;
using matrix = std::vector<std::vector<real_t>>;

urng_t pseudo_random_engine_from_device();
