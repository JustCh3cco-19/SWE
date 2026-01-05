#pragma once

#include "parser.hpp"

#include "mocc.hpp"

double EstimateExpectedCost(
    const MdpData& data,
    int simulations,
    urng_t* rng
);
