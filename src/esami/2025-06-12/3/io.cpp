#include "io.hpp"

#include <fstream>
#include <iomanip>

#include "exam_utils.hpp"

bool WriteResults(
    const std::string& path,
    const std::vector<OutputRecord>& records,
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
  for (const auto& record : records) {
    output << record.time << " " << record.value << "\n";
  }
  return true;
}
