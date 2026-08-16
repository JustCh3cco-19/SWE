#include <iostream>
#include <iomanip>
#include <string>

#include <mocc/exam_utils.hpp>
#include <probability-and-statistics/2025-11-03-ex1/parser.hpp>
#include <probability-and-statistics/2025-11-03-ex1/simulation.hpp>

int main() {
  const mocc_utils::UserInfo user = mocc_utils::GetUserInfo();
  Parameters params;
  std::string error;
  if (!LoadParameters("parameters.txt", &params, &error)) {
    std::cerr << error << "\n";
    return 1;
  }

  auto rng = mocc_utils::MakeRng();
  double value = EstimateExpectedCost(params, &rng);

  if (!mocc_utils::WriteResultsToFile("results.txt",
                                      user.nome,
                                      user.cognome,
                                      user.matricola, [&](std::ostream& output) {
    output << std::setprecision(8) << value << "\n";
  }, &error)) {
    std::cerr << error << "\n";
    return 1;
  }
  return 0;
}
