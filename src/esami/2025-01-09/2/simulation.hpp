#pragma once

#include "parser.hpp"

#include "mocc.hpp"

double EstimateProbability(
    const MdpData& data,
    double cost_limit,
    int simulations,
    urng_t* rng
);
