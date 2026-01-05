#pragma once

#include <string>

bool WriteResults(
    const std::string& path,
    double best_fraction,
    double best_alpha,
    std::string* error
);
