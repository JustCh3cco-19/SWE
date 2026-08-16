#include <iostream>
#include <string>
#include <iomanip>

#include <mocc/exam_utils.hpp>
#include <optimization/2025-03-21-ex5/parser.hpp>
#include <optimization/2025-03-21-ex5/simulation.hpp>

int main() {
  const mocc_utils::UserInfo user = mocc_utils::GetUserInfo();
  Parameters params;
  std::string error;
  if (!LoadParameters("parameters.txt", &params, &error)) {
    std::cerr << error << "\n";
    return 1;
  }

  auto rng = mocc_utils::MakeRng();
  OptimizationResult result = OptimizeAlpha(params, 1000, &rng);

  if (!mocc_utils::WriteResultsToFile("results.txt",
                                      user.nome,
                                      user.cognome,
                                      user.matricola,
                                      [&result](std::ostream& output) {
    output << std::setprecision(6);
    output << "A " << result.alpha << "\n";
    output << "W " << result.w_rate << "\n";
    output << "S " << result.s_rate << "\n";
    output << "J " << result.j_value << "\n";
  },
                                      &error)) {
    std::cerr << error << "\n";
    return 1;
  }

  return 0;
}
