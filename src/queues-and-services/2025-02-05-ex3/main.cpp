#include <iostream>
#include <string>
#include <iomanip>

#include <mocc/exam_utils.hpp>
#include <queues-and-services/2025-02-05-ex3/parser.hpp>
#include <queues-and-services/2025-02-05-ex3/simulation.hpp>

int main() {
  const mocc_utils::UserInfo user = mocc_utils::GetUserInfo();
  Parameters params;
  std::string error;
  if (!LoadParameters("parameters.txt", &params, &error)) {
    std::cerr << error << "\n";
    return 1;
  }

  auto rng = mocc_utils::MakeRng();
  double average = EstimateThroughput(params, 1000, &rng);

  if (!mocc_utils::WriteResultsToFile("results.txt",
                                      user.nome,
                                      user.cognome,
                                      user.matricola,
                                      [average](std::ostream& output) {
    output << std::setprecision(6);
    output << "Avg " << average << "\n";
  },
                                      &error)) {
    std::cerr << error << "\n";
    return 1;
  }

  return 0;
}
