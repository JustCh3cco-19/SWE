#include <iostream>
#include <string>
#include <iomanip>

#include <mocc/exam_utils.hpp>
#include <ecommerce/2025-03-21-ex3/parser.hpp>
#include <ecommerce/2025-03-21-ex3/simulation.hpp>

int main() {
  const mocc_utils::UserInfo user = mocc_utils::GetUserInfo();
  Parameters params;
  std::string error;
  if (!LoadParameters("parameters.txt", &params, &error)) {
    std::cerr << error << "\n";
    return 1;
  }

  auto rng = mocc_utils::MakeRng();
  double oversellings = EstimateOversellings(params, 1000, &rng);

  if (!mocc_utils::WriteResultsToFile("results.txt",
                                      user.nome,
                                      user.cognome,
                                      user.matricola,
                                      [oversellings, &params](std::ostream& output) {
    double rate = (params.num_servers > 0 && params.horizon > 0)
                                            ? oversellings /
                  (params.num_servers * static_cast<double>(params.horizon))
                                            : 0.0;
    output << std::setprecision(6);
    output << "S " << oversellings << "\n";
    output << "R " << rate << "\n";
  },
                                      &error)) {
    std::cerr << error << "\n";
    return 1;
  }

  return 0;
}
