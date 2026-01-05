#include "io.hpp"

#include <fstream>
#include <iomanip>

#include "exam_utils.hpp"

bool WriteResults(
    const std::string& path,
    double alpha,
    double w_rate,
    double s_rate,
    double j_value,
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
  output << "A " << alpha << "\n";
  output << "W " << w_rate << "\n";
  output << "S " << s_rate << "\n";
  output << "J " << j_value << "\n";
  return true;
}
