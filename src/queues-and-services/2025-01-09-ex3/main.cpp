#include <iostream>
#include <string>

#include <mocc/exam_utils.hpp>
#include <queues-and-services/2025-01-09-ex3/parser.hpp>
#include <queues-and-services/2025-01-09-ex3/simulation.hpp>

int main() {
  const mocc_utils::UserInfo user = mocc_utils::GetUserInfo();
  Parameters params;
  std::string error;
  if (!LoadParameters("parameters.txt", &params, &error)) {
    std::cerr << error << "\n";
    return 1;
  }

  auto rng = mocc_utils::MakeRng();
  Stats stats = SimulateCustomer(params.avg, params.stddev, 1000000, &rng);

  if (!mocc_utils::WriteResultsToFile("results.txt",
                                      user.nome,
                                      user.cognome,
                                      user.matricola,
                                      [&stats](std::ostream& output) {
    output << "Avg " << stats.avg << "\n";
    output << "StdDev " << stats.stddev << "\n";
  },
                                      &error)) {
    std::cerr << error << "\n";
    return 1;
  }

  return 0;
}
