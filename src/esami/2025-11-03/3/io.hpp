#pragma once

#include <string>

bool WriteResults(
    const std::string& path,
    double best_p,
    double expected_cost,
    double total_cost,
    std::string* error
);
