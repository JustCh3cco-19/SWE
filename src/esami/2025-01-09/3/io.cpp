#include "io.hpp"

#include <fstream>

#include "exam_utils.hpp"

bool WriteResults(
    const std::string& path,
    double avg,
    double stddev,
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
  output << "Avg " << avg << "\n";
  output << "StdDev " << stddev << "\n";
  return true;
}
