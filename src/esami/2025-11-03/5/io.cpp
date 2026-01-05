#include "io.hpp"

#include <fstream>
#include <iomanip>

#include "exam_utils.hpp"

bool WriteResults(
    const std::string& path,
    double best_p,
    double rate,
    double cost,
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
  output << "R " << rate << "\n";
  output << "J " << cost << "\n";
  return true;
}
