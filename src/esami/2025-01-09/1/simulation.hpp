#pragma once

#include "exam_utils.hpp"
#include "mocc.hpp"

double EstimateExpectedCost(
    const mocc_utils::MdpData& data,
    int simulations,
    urng_t* rng
);
