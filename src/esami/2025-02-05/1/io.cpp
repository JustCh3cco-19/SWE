#include "io.hpp"

#include <fstream>
#include <iomanip>

#include "exam_utils.hpp"

bool WriteResults(
    const std::string& path,
    const std::vector<double>& coverage,
    const std::vector<Point>& points,
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
  for (std::size_t i = 0; i < points.size(); ++i) {
    double value = (i < coverage.size()) ? coverage[i] : 0.0;
    output << points[i].x << " " << points[i].y << " " << value << "\n";
  }
  return true;
}
