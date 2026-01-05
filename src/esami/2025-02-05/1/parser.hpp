#pragma once

#include <string>
#include <vector>

struct Point {
  double x = 0.0;
  double y = 0.0;
};

struct Parameters {
  int horizon = 0;
  int num_drones = 0;
  double x1 = 0.0;
  double x2 = 0.0;
  double y1 = 0.0;
  double y2 = 0.0;
  std::vector<Point> points;
};

bool LoadParameters(const std::string& path, Parameters* out, std::string* error);
