#include <probability-and-statistics/2025-01-09-ex2/parser.hpp>

#include <utility>

#include <mocc/exam_utils.hpp>

namespace {

struct EdgeRecord {
  int from;
  int to;
  double prob;
  double cost;
};

}  // namespace

bool LoadParameters(const std::string& path, Parameters*out, std::string*error) {
  if (!out) {
    return false;
  }

  double cost_limit = 0.0;
  int num_states = -1;
  std::vector<EdgeRecord> edges;
  bool cost_limit_set = false;

  bool success = mocc_utils::ParseTaggedFile(path,
                                             [&](std::istringstream& row, const std::string&) {
    std::string tag;
    row >> tag;
    if (tag == "C") {
      row >> cost_limit;
      cost_limit_set = true;
    } else if (tag == "N") {
      row >> num_states;
    } else if (tag == "A") {
      int from = -1;
      int to = -1;
      double prob = 0.0;
      double cost = 0.0;
      if (row >> from >> to >> prob >> cost) {
        edges.push_back(EdgeRecord{from, to, prob, cost});
      }
    }
  }, error);

  if (!success) {
    return false;
  }

  if (!cost_limit_set) {
    if (error) {
      *error = "Missing cost limit (C) in parameters.txt";
    }
    return false;
  }

  if (num_states <= 0) {
    int max_state = -1;
    for (const auto& e : edges) {
      if (e.from > max_state) {
        max_state = e.from;
      }
      if (e.to > max_state) {
        max_state = e.to;
      }
    }
    if (max_state < 0) {
      if (error) {
        *error = "No states found in parameters.txt";
      }
      return false;
    }
    num_states = max_state + 1;
  }

  std::vector<std::vector<mocc_utils::Transition> > transitions(num_states);
  for (const auto& e : edges) {
    if (e.from < 0 || e.from >= num_states) {
      continue;
    }
    transitions[e.from].push_back(mocc_utils::Transition{e.to, e.prob, e.cost});
  }

  out->cost_limit = cost_limit;
  out->mdp.num_states = num_states;
  out->mdp.transitions = std::move(transitions);
  return true;
}
