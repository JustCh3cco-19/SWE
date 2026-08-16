#pragma once

#include <mocc/exam_utils.hpp>
#include <mocc/mocc.hpp>

double EstimateProbability(
  const mocc_utils::MdpData& data,
  double cost_limit,
  int simulations,
  urng_t*rng
  );
