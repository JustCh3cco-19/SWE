#include <iostream>
#include <iomanip>
#include <string>

#include <mocc/exam_utils.hpp>
#include <ecommerce/2025-06-12-ex3/parser.hpp>
#include <ecommerce/2025-06-12-ex3/simulation.hpp>

int main() {
  const mocc_utils::UserInfo user = mocc_utils::GetUserInfo();
  Parameters params;
  std::string error;
  if (!LoadParameters("parameters.txt", &params, &error)) {
    std::cerr << error << "\n";
    return 1;
  }

  auto rng = mocc_utils::MakeRng();
  std::vector<OutputRecord> records = SimulateCustomer(params, &rng);

  if (!mocc_utils::WriteResultsToFile("results.txt",
                                      user.nome,
                                      user.cognome,
                                      user.matricola, [&](std::ostream& output) {
    output << std::setprecision(8);
    for (const auto& rec : records) {
      output << rec.time << " " << rec.value << "\n";
    }
  }, &error)) {
    std::cerr << error << "\n";
    return 1;
  }
  return 0;
}
