#include <probability-and-statistics/2025-01-09-ex1/parser.hpp>

#include <utility>

#include <mocc/exam_utils.hpp>

bool LoadParameters(const std::string& path, mocc_utils::MdpData*out, std::string*error) {
  if (!out) {
    return false;
  }

  int num_states = -1;
  std::vector<std::vector<mocc_utils::Transition> > transitions;

  bool success = mocc_utils::ParseTaggedFile(path,
                                             [&num_states, &transitions](std::istringstream& row,
                                                                         const std::string&) {
    std::string tag;
    row >> tag;
    if (tag == "N") {
      row >> num_states;
      if (num_states > 0) {
        transitions.resize(num_states);
      }
    } else if (tag == "A") {
      int from = -1;
      int to = -1;
      double prob = 0.0;
      double cost = 0.0;
      if (row >> from >> to >> prob >> cost) {
        if (from >= 0 && from < num_states) {
          transitions[from].push_back(mocc_utils::Transition{to, prob, cost});
        }
      }
    }
  }, error);

  if (!success) {
    return false;
  }

  if (num_states <= 0) {
    if (error) {
      *error = "Invalid or missing header in parameters.txt";
    }
    return false;
  }

  out->num_states = num_states;
  out->transitions = std::move(transitions);
  return true;
}
