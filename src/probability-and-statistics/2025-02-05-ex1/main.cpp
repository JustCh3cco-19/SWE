#include <iostream>
#include <string>
#include <iomanip>

#include <mocc/exam_utils.hpp>
#include <probability-and-statistics/2025-02-05-ex1/parser.hpp>
#include <probability-and-statistics/2025-02-05-ex1/simulation.hpp>

int main() {
  const mocc_utils::UserInfo user = mocc_utils::GetUserInfo();
  Parameters params;
  std::string error;
  if (!LoadParameters("parameters.txt", &params, &error)) {
    std::cerr << error << "\n";
    return 1;
  }

  auto rng = mocc_utils::MakeRng();
  std::vector<double> coverage = SimulateCoverage(params, &rng);

  if (!mocc_utils::WriteResultsToFile("results.txt",
                                      user.nome,
                                      user.cognome,
                                      user.matricola,
                                      [&coverage, &params](std::ostream& output) {
    output << std::setprecision(6);
    for (std::size_t i = 0; i < params.points.size(); ++i) {
      double value = (i < coverage.size()) ? coverage[i] : 0.0;
      output << params.points[i].x << " " << params.points[i].y << " " << value << "\n";
    }
  },
                                      &error)) {
    std::cerr << error << "\n";
    return 1;
  }

  return 0;
}
