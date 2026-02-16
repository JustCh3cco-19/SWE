#include "parameters.h"

#include "../mocc/exam_utils.hpp"

#include <cmath>
#include <iostream>
#include <sstream>
#include <string>

bool ReadParameters(const std::string& path, Parameters& out) {
  bool parse_ok = true;
  std::string error;

  auto processor = [&](std::istringstream& row, const std::string&) {
    std::string key;
    double value = 0.0;
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
    } else if (key == "C") {
      out.C = static_cast<int>(std::llround(value));
    } else if (key == "A") {
      out.A = value;
    } else if (key == "B") {
      out.B = value;
    } else if (key == "Q") {
      out.Q = static_cast<int>(std::llround(value));
    } else if (key == "V") {
      out.V = value;
    } else if (key == "W") {
      out.W = value;
    } else if (key == "P") {
      out.P = static_cast<int>(std::llround(value));
    } else if (key == "S") {
      out.S = static_cast<int>(std::llround(value));
    } else if (key == "F") {
      out.F = static_cast<int>(std::llround(value));
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

  bool ok = out.T > 0.0 && out.H > 0.0 && out.M > 0 && out.C > 0 &&
            out.A > 0.0 && out.B > 0.0 && out.Q > 0 && out.V > 0.0 &&
            out.W > 0.0 && out.P > 0 && out.S > 0 && out.F > 0;
  if (!ok) {
    std::cerr << "Missing or invalid parameters in " << path << "\n";
  }
  return ok;
}
