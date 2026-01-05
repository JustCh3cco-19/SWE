#include <iostream>
#include <string>

#include "exam_utils.hpp"
#include "io.hpp"
#include "parser.hpp"
#include "simulation.hpp"

int main() {
  MdpData data;
  std::string error;
  if (!LoadParameters("parameters.txt", &data, &error)) {
    std::cerr << error << "\n";
    return 1;
  }

  auto rng = mocc_utils::MakeRng();
  double average = EstimateExpectedCost(data, 1000, &rng);

  if (!WriteResults("results.txt", average, &error)) {
    std::cerr << error << "\n";
    return 1;
  }

  return 0;
}
