#include <queues-and-services/2025-01-09-ex3/parser.hpp>

#include <mocc/exam_utils.hpp>

bool LoadParameters(const std::string& path, Parameters*out, std::string*error) {
  if (!out) {
    return false;
  }

  return mocc_utils::ParseTaggedFile(path,
                                     [out](std::istringstream& row, const std::string&) {
    std::string tag;
    row >> tag;
    if (tag == "Avg") {
      row >> out->avg;
    } else if (tag == "StdDev") {
      row >> out->stddev;
    }
  }, error);
}
