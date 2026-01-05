#pragma once

#include <filesystem>
#include <string>

#include "mocc.hpp"

namespace mocc_utils {

inline bool IsAllDigits(const std::string& s) {
  if (s.empty()) {
    return false;
  }
  for (char ch : s) {
    if (ch < '0' || ch > '9') {
      return false;
    }
  }
  return true;
}

inline std::string RootNameFromCwd() {
  std::filesystem::path cwd = std::filesystem::current_path();
  std::string cwd_name = cwd.filename().string();
  if (IsAllDigits(cwd_name)) {
    return cwd.parent_path().filename().string();
  }
  return cwd_name;
}

inline urng_t MakeRng() { return urng_t(0); }

}  // namespace mocc_utils
