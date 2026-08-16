#include <iostream>
#include <string>

#include <mocc/exam_utils.hpp>
#include <probability-and-statistics/2025-01-09-ex1/parser.hpp>
#include <probability-and-statistics/2025-01-09-ex1/simulation.hpp>

int main() {
  const mocc_utils::UserInfo user = mocc_utils::GetUserInfo();
  mocc_utils::MdpData data;
  std::string error;
  if (!LoadParameters("parameters.txt", &data, &error)) {
    std::cerr << error << "\n";
    return 1;
  }

  auto rng = mocc_utils::MakeRng();
  double average = EstimateExpectedCost(data, 1000, &rng);

  if (!mocc_utils::WriteResultsToFile("results.txt",
                                      user.nome,
                                      user.cognome,
                                      user.matricola,
                                      [average](std::ostream& output) {
    output << "C " << average << "\n";
  },
                                      &error)) {
    std::cerr << error << "\n";
    return 1;
  }

  return 0;
}
