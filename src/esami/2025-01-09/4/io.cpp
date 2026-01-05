#include "io.hpp"

#include <fstream>

#include "exam_utils.hpp"

bool WriteResults(
    const std::string& path,
    const std::vector<long long>& counts,
    long long total_messages,
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
  for (std::size_t i = 0; i < counts.size(); ++i) {
    output << (i + 1) << " " << counts[i] << "\n";
  }
  output << "M1 " << total_messages << "\n";
  return true;
}
