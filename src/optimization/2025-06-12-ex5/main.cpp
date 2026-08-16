#include <iostream>
#include <iomanip>
#include <string>

#include <mocc/exam_utils.hpp>
#include <optimization/2025-06-12-ex5/parser.hpp>
#include <optimization/2025-06-12-ex5/simulation.hpp>

int main() {
  const mocc_utils::UserInfo user = mocc_utils::GetUserInfo();
  Parameters params;
  std::string error;
  if (!LoadParameters("parameters.txt", &params, &error)) {
    std::cerr << error << "\n";
    return 1;
  }

  auto rng = mocc_utils::MakeRng();
  OptimizationResult result = OptimizeP(params, &rng);

  if (!mocc_utils::WriteResultsToFile("results.txt",
                                      user.nome,
                                      user.cognome,
                                      user.matricola, [&](std::ostream& output) {
    output << std::setprecision(8) << "P " << result.best_p << "\n";
    output << "Q " << result.best_q << "\n";
  }, &error)) {
    std::cerr << error << "\n";
    return 1;
  }
  return 0;
}
