#include <optimization/2025-03-21-ex5/parser.hpp>

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

namespace {

std::vector<double> ParseLineDoubles(const std::string& line) {
  std::vector<double> values;
  std::istringstream row(line);
  double value = 0.0;
  while (row >> value) {
    values.push_back(value);
  }
  return values;
}

}  // namespace

bool LoadParameters(const std::string& path, Parameters*out, std::string*error) {
  if (!out) {
    return false;
  }

  std::ifstream input(path);
  if (!input) {
    if (error) {
      *error = "Cannot open parameters.txt";
    }
    return false;
  }

  std::string line;
  std::vector<double> p_line;
  std::vector<double> f_line;
  std::vector<std::vector<double> > numeric_lines;
  while (std::getline(input, line)) {
    if (line.empty()) {
      continue;
    }
    std::istringstream row(line);
    std::string tag;
    row >> tag;
    if (tag == "H") {
      double value = 0.0;
      row >> value;
      out->horizon = static_cast<int>(value);
    } else if (tag == "n") {
      row >> out->num_servers;
    } else if (tag == "k") {
      row >> out->num_products;
    } else if (tag == "p0") {
      p_line = ParseLineDoubles(line);
    } else if (tag == "f0") {
      f_line = ParseLineDoubles(line);
    } else {
      std::vector<double> values = ParseLineDoubles(line);
      if (!values.empty()) {
        numeric_lines.push_back(values);
      }
    }
  }

  if (out->horizon <= 0 && numeric_lines.size() >= 1 && numeric_lines[0].size() == 1) {
    out->horizon = static_cast<int>(numeric_lines[0][0]);
  }
  if (out->num_servers <= 0 && numeric_lines.size() >= 2 && numeric_lines[1].size() == 1) {
    out->num_servers = static_cast<int>(numeric_lines[1][0]);
  }
  if (out->num_products <= 0 && numeric_lines.size() >= 3 && numeric_lines[2].size() == 1) {
    out->num_products = static_cast<int>(numeric_lines[2][0]);
  }
  if (p_line.empty() && numeric_lines.size() >= 4) {
    p_line = numeric_lines[3];
  }
  if (f_line.empty() && numeric_lines.size() >= 5) {
    f_line = numeric_lines[4];
  }

  if (out->num_products > 0) {
    if (p_line.size() == static_cast<std::size_t>(out->num_products + 1)) {
      out->customer_probs = p_line;
    }
    if (f_line.size() == static_cast<std::size_t>(out->num_products + 1)) {
      out->supplier_probs = f_line;
    }
  }

  if (out->horizon <= 0 || out->num_servers <= 0 || out->num_products <= 0) {
    if (error) {
      *error = "Invalid parameters.txt";
    }
    return false;
  }
  if (out->customer_probs.empty() || out->supplier_probs.empty()) {
    if (error) {
      *error = "Missing probability vectors";
    }
    return false;
  }

  return true;
}
