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
  int active = SimulateOperational(params, &rng);

  if (!mocc_utils::WriteResultsToFile("results.txt",
                                      user.nome,
                                      user.cognome,
                                      user.matricola,
                                      [active, &params](std::ostream& output) {
                                        double fraction = (params.num_drones > 0) ? static_cast<double>(active) / params.num_drones : 0.0;
                                        output << "Q " << active << "\n";
                                        output << "N " << params.num_drones << "\n";
                                        output << std::setprecision(6);
                                        output << "P " << fraction << "\n";
                                      },
                                      &error)) {
    std::cerr << error << "\n";
    return 1;
  }

  return 0;
}
