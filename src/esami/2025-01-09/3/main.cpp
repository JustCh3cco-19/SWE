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
  Stats stats = SimulateCustomer(params.avg, params.stddev, 1000000, &rng);

  if (!WriteResults("results.txt", stats.avg, stats.stddev, &error)) {
    std::cerr << error << "\n";
    return 1;
  }

  return 0;
}
