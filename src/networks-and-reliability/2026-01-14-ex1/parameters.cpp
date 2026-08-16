#include <networks-and-reliability/2026-01-14-ex1/parameters.hpp>

#include <mocc/exam_utils.hpp>

#include <cmath>
#include <iostream>
#include <sstream>
#include <string>

bool ReadParameters(const std::string& path, Parameters& out) {
  bool parse_ok = true;
  std::string error;

  auto processor = [&](std::istringstream& row, const std::string&) {
                     std::string key;
                     real_t value = 0.0;
                     if (!(row >> key >> value)) {
                       parse_ok = false;
                       return;
                     }

                     if (key == "T") {
                       out.T = value;
                     } else if (key == "H") {
                       out.H = value;
                     } else if (key == "M") {
                       out.M = static_cast<int>(std::llround(value));
                     } else if (key == "N") {
                       out.N = static_cast<int>(std::llround(value));
                     } else if (key == "L") {
                       out.L = value;
                     } else if (key == "V") {
                       out.V = value;
                     } else if (key == "A") {
                       out.A = value;
                     } else if (key == "D") {
                       out.D = value;
                     } else if (key == "R") {
                       out.R = value;
                     }
                   };

  if (!mocc_utils::ParseTaggedFile(path, processor, &error) || !parse_ok) {
    if (!error.empty()) {
      std::cerr << error << "\n";
    } else {
      std::cerr << "Invalid format in " << path << "\n";
    }
    return false;
  }

  bool ok = out.T > 0.0 && out.H > 0.0 && out.M > 0 && out.N > 0 &&
            out.L > 0.0 && out.V > 0.0 && out.A > 0.0 && out.D > 0.0 &&
            out.R > 0.0;
  if (!ok) {
    std::cerr << "Missing or invalid parameters in " << path << "\n";
  }
  return ok;
}
