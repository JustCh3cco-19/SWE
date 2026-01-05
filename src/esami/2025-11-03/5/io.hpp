#pragma once

#include <string>

bool WriteResults(
    const std::string& path,
    double best_p,
    double rate,
    double cost,
    std::string* error
);
