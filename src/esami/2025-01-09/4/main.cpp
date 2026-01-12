#include <iostream>
#include <string>

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
  DispatcherResult result =
      SimulateDispatcher(params.num_customers, params.avg, params.stddev, 1000000, &rng);

  if (!mocc_utils::WriteResultsToFile("results.txt",
                                      user.nome,
                                      user.cognome,
                                      user.matricola,
                                      [&result](std::ostream& output) {
                                        for (std::size_t i = 0; i < result.counts.size(); ++i) {
                                          output << (i + 1) << " " << result.counts[i] << "\n";
                                        }
                                        output << "M1 " << result.total_messages << "\n";
                                      },
                                      &error)) {
    std::cerr << error << "\n";
    return 1;
  }

  return 0;
}
