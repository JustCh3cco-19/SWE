#include <iostream>
#include <string>
#include <iomanip>

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
  double transactions = EstimateTransactions(params, 1000, &rng);

  if (!mocc_utils::WriteResultsToFile("results.txt",
                                      user.nome,
                                      user.cognome,
                                      user.matricola,
                                      [transactions, &params](std::ostream& output) {
                                        double rate = (params.num_servers > 0 && params.horizon > 0)
                                            ? transactions / (params.num_servers * static_cast<double>(params.horizon))
                                            : 0.0;
                                        output << std::setprecision(6);
                                        output << "Z " << transactions << "\n";
                                        output << "W " << rate << "\n";
                                      },
                                      &error)) {
    std::cerr << error << "\n";
    return 1;
  }

  return 0;
}
