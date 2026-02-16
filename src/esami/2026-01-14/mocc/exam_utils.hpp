#pragma once

#include <filesystem>
#include <fstream>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

#include "mocc.hpp"

namespace mocc_utils {

struct Transition {
  int to;
  double prob;
  double cost;
};

struct MdpData {
  int num_states = 0;
  std::vector<std::vector<Transition>> transitions;
};

struct Point {
  double x = 0.0;
  double y = 0.0;
};

struct UserInfo {
  std::string nome;
  std::string cognome;
  std::string matricola;
};

inline UserInfo GetUserInfo() {
  return {"Nome", "Cognome", "Matricola"};
}

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

inline void WriteResultsHeader(std::ostream& output) {
  output << RootNameFromCwd() << "\n";
}

inline void WriteResultsHeader(std::ostream& output,
                               const std::string& nome,
                               const std::string& cognome,
                               const std::string& matricola) {
  output << RootNameFromCwd() << "-" << nome << "-" << cognome << "-" << matricola << "\n";
}

template<typename WriterFunc>
inline bool WriteResultsToFile(
    const std::string& path,
    WriterFunc writer,
    std::string* error = nullptr
) {
  std::ofstream output(path);
  if (!output) {
    if (error) {
      *error = "Cannot open results.txt";
    }
    return false;
  }
  
  WriteResultsHeader(output);
  writer(output);
  return true;
}

template<typename WriterFunc>
inline bool WriteResultsToFile(
    const std::string& path,
    const std::string& nome,
    const std::string& cognome,
    const std::string& matricola,
    WriterFunc writer,
    std::string* error = nullptr
) {
  std::ofstream output(path);
  if (!output) {
    if (error) {
      *error = "Cannot open results.txt";
    }
    return false;
  }
  
  WriteResultsHeader(output, nome, cognome, matricola);
  writer(output);
  return true;
}

template<typename ProcessorFunc>
inline bool ParseTaggedFile(
    const std::string& path,
    ProcessorFunc processor,
    std::string* error = nullptr
) {
  std::ifstream input(path);
  if (!input) {
    if (error) {
      *error = "Cannot open " + path;
    }
    return false;
  }

  std::string line;
  while (std::getline(input, line)) {
    if (line.empty()) {
      continue;
    }
    std::istringstream row(line);
    processor(row, line);
  }
  
  return true;
}

inline bool ParseNumbers(const std::string& line, std::vector<double>* values) {
  if (!values) {
    return false;
  }
  values->clear();
  std::istringstream row(line);
  double value = 0.0;
  while (row >> value) {
    values->push_back(value);
  }
  return !values->empty();
}

inline urng_t MakeRng() {
  std::random_device rd;
  return urng_t(rd());
}

}
