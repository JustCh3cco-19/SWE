#include "io.hpp"

#include <fstream>

#include "exam_utils.hpp"

bool WriteResults(const std::string& path, double probability, std::string* error) {
  std::ofstream output(path);
  if (!output) {
    if (error) {
      *error = "Cannot open results.txt";
    }
    return false;
  }

  output << mocc_utils::RootNameFromCwd() << "\n";
  output << "P " << probability << "\n";
  return true;
}
