#pragma once

#include <string>
#include <vector>

#include "simulation.hpp"

bool WriteResults(
    const std::string& path,
    const std::vector<OutputRecord>& records,
    std::string* error
);
