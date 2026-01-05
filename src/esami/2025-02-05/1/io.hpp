#pragma once

#include <string>
#include <vector>

#include "parser.hpp"

bool WriteResults(
    const std::string& path,
    const std::vector<double>& coverage,
    const std::vector<Point>& points,
    std::string* error
);
