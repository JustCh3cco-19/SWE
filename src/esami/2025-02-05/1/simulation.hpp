#pragma once

#include <vector>

#include "mocc.hpp"
#include "parser.hpp"

std::vector<double> SimulateCoverage(
    const Parameters& params,
    urng_t* rng
);
