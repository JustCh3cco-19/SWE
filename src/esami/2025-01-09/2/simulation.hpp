#pragma once

#include "exam_utils.hpp"
#include "mocc.hpp"

double EstimateProbability(
    const mocc_utils::MdpData& data,
    double cost_limit,
    int simulations,
    urng_t* rng
);
