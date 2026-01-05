#include "io.hpp"

#include <fstream>
#include <iomanip>

#include "exam_utils.hpp"

bool WriteResults(
    const std::string& path,
    double best_p,
    double expected_cost,
    double total_cost,
    std::string* error
) {
  std::ofstream output(path);
  if (!output) {
    if (error) {
      *error = "Cannot open results.txt";
    }
    return false;
  }

  output << mocc_utils::RootNameFromCwd() << "\n";
  output << std::setprecision(6);
  output << "p " << best_p << "\n";
  output << "C " << expected_cost << "\n";
  output << "J " << total_cost << "\n";
  return true;
}
