#include "io.hpp"

#include <fstream>
#include <iomanip>

#include "exam_utils.hpp"

bool WriteResults(
    const std::string& path,
    int active,
    int total,
    std::string* error
) {
  std::ofstream output(path);
  if (!output) {
    if (error) {
      *error = "Cannot open results.txt";
    }
    return false;
  }

  double fraction = (total > 0) ? static_cast<double>(active) / total : 0.0;
  output << mocc_utils::RootNameFromCwd() << "\n";
  output << "Q " << active << "\n";
  output << "N " << total << "\n";
  output << std::setprecision(6);
  output << "P " << fraction << "\n";
  return true;
}
