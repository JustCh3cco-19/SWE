#include "io.hpp"

#include <fstream>
#include <iomanip>

#include "exam_utils.hpp"

bool WriteResults(
    const std::string& path,
    double rate,
    double v_value,
    double q_value,
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
  output << "R " << rate << "\n";
  output << "V " << v_value << "\n";
  output << "Q " << q_value << "\n";
  output << "J " << cost << "\n";
  return true;
}
