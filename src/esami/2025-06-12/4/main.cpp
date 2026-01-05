#include <iostream>
#include <string>

#include "exam_utils.hpp"
#include "io.hpp"
#include "parser.hpp"
#include "simulation.hpp"

int main() {
  Parameters params;
  std::string error;
  if (!LoadParameters("parameters.txt", &params, &error)) {
    std::cerr << error << "\n";
    return 1;
  }

  auto rng = mocc_utils::MakeRng();
  double q_value = EstimateFailureRate(params, &rng);

  if (!WriteResults("results.txt", q_value, &error)) {
    std::cerr << error << "\n";
    return 1;
  }

  return 0;
}
