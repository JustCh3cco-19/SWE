#include "io.hpp"

#include <fstream>
#include <iomanip>

#include "exam_utils.hpp"

bool WriteResults(
    const std::string& path,
    double oversellings,
    int num_servers,
    int horizon,
    std::string* error
) {
  std::ofstream output(path);
  if (!output) {
    if (error) {
      *error = "Cannot open results.txt";
    }
    return false;
  }

  double rate = (num_servers > 0 && horizon > 0)
      ? oversellings / (num_servers * static_cast<double>(horizon))
      : 0.0;

  output << mocc_utils::RootNameFromCwd() << "\n";
  output << std::setprecision(6);
  output << "S " << oversellings << "\n";
  output << "R " << rate << "\n";
  return true;
}
