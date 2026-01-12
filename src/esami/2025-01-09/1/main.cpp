#include <iostream>
#include <string>

#include "exam_utils.hpp"
#include "parser.hpp"
#include "simulation.hpp"

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
