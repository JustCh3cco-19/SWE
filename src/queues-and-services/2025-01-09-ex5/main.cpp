#include <iostream>
#include <string>

#include <mocc/exam_utils.hpp>
#include <queues-and-services/2025-01-09-ex5/parser.hpp>
#include <queues-and-services/2025-01-09-ex5/simulation.hpp>

int main() {
  const mocc_utils::UserInfo user = mocc_utils::GetUserInfo();
  Parameters params;
  std::string error;
  if (!LoadParameters("parameters.txt", &params, &error)) {
    std::cerr << error << "\n";
    return 1;
  }

  auto rng = mocc_utils::MakeRng();
  DispatcherResult result = SimulateDispatcher(
    params.num_customers,
    params.avg,
    params.stddev,
    1000000,
    &rng
    );

  if (!mocc_utils::WriteResultsToFile("results.txt",
                                      user.nome,
                                      user.cognome,
                                      user.matricola,
                                      [&result](std::ostream& output) {
    for (std::size_t i = 0; i < result.counts.size(); ++i) {
      output << (i + 1) << " " << result.counts[i] << "\n";
    }
    output << "M2 " << (result.violation ? 1 : 0) << "\n";
  },
                                      &error)) {
    std::cerr << error << "\n";
    return 1;
  }

  return 0;
}
