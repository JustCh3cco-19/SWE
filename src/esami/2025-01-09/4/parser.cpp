#include "parser.hpp"

#include "exam_utils.hpp"

bool LoadParameters(const std::string& path, Parameters* out, std::string* error) {
  if (!out) {
    return false;
  }

  bool success = mocc_utils::ParseTaggedFile(path,
    [out](std::istringstream& row, const std::string&) {
      std::string tag;
      row >> tag;
      if (tag == "N") {
        row >> out->num_customers;
      } else if (tag == "Avg") {
        row >> out->avg;
      } else if (tag == "StdDev") {
        row >> out->stddev;
      }
    }, error);

  if (success && out->num_customers <= 0) {
    if (error) {
      *error = "Invalid number of customers";
    }
    return false;
  }

  return success;
}
