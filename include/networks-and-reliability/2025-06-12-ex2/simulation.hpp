#pragma once

#include <mocc/mocc.hpp>
#include <networks-and-reliability/2025-06-12-ex2/parser.hpp>

double EstimateCollisionInterval(const Parameters& params, int simulations, urng_t*rng);
