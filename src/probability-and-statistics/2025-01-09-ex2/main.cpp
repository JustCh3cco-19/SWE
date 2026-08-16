#include <iostream>
#include <string>

#include <mocc/exam_utils.hpp>
#include <probability-and-statistics/2025-01-09-ex2/parser.hpp>
#include <probability-and-statistics/2025-01-09-ex2/simulation.hpp>

int main() {
  const mocc_utils::UserInfo user = mocc_utils::GetUserInfo();
  Parameters params;
  std::string error;
  if (!LoadParameters("parameters.txt", &params, &error)) {
    std::cerr << error << "\n";
    return 1;
  }

  auto rng = mocc_utils::MakeRng();
  double probability =
    EstimateProbability(params.mdp, params.cost_limit, 1000, &rng);

  if (!mocc_utils::WriteResultsToFile("results.txt",
                                      user.nome,
                                      user.cognome,
                                      user.matricola,
                                      [probability](std::ostream& output) {
    output << "P " << probability << "\n";
  },
                                      &error)) {
    std::cerr << error << "\n";
    return 1;
  }

  return 0;
}
