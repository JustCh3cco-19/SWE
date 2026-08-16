#include <iostream>
#include <iomanip>
#include <string>

#include <mocc/exam_utils.hpp>
#include <networks-and-reliability/2025-06-12-ex4/parser.hpp>
#include <networks-and-reliability/2025-06-12-ex4/simulation.hpp>

int main() {
  const mocc_utils::UserInfo user = mocc_utils::GetUserInfo();
  Parameters params;
  std::string error;
  if (!LoadParameters("parameters.txt", &params, &error)) {
    std::cerr << error << "\n";
    return 1;
  }

  auto rng = mocc_utils::MakeRng();
  double q_value = EstimateFailureRate(params, &rng);

  if (!mocc_utils::WriteResultsToFile("results.txt",
                                      user.nome,
                                      user.cognome,
                                      user.matricola, [&](std::ostream& output) {
    output << std::setprecision(8) << "Q " << q_value << "\n";
  }, &error)) {
    std::cerr << error << "\n";
    return 1;
  }

  return 0;
}
