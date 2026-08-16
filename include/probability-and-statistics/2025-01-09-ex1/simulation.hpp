#pragma once

#include <mocc/exam_utils.hpp>
#include <mocc/mocc.hpp>

double EstimateExpectedCost(
  const mocc_utils::MdpData& data,
  int simulations,
  urng_t*rng
  );
