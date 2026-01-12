#include <iostream>
#include <iomanip>
#include <string>

#include "exam_utils.hpp"
#include "parser.hpp"
#include "simulation.hpp"

int main() {
  const mocc_utils::UserInfo user = mocc_utils::GetUserInfo();
  Parameters params;
  std::string error;
  if (!LoadParameters("parameters.txt", &params, &error)) {
    std::cerr << error << "\n";
    return 1;
  }

  auto rng = mocc_utils::MakeRng();
  OptimizationResult result = OptimizeSupply(params, &rng);

  if (!mocc_utils::WriteResultsToFile(
          "results.txt",
          user.nome,
          user.cognome,
          user.matricola, [&](std::ostream& output) {
    output << std::setprecision(8) << "R " << result.best_rate << "\n";
    output << "V " << result.best_v << "\n";
    output << "Q " << result.best_q << "\n";
    output << "J " << result.best_cost << "\n";
  },
          &error)) {
    std::cerr << error << "\n";
    return 1;
  }
  return 0;
}
