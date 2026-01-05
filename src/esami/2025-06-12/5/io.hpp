#pragma once

#include <string>

bool WriteResults(
    const std::string& path,
    double best_p,
    double best_q,
    std::string* error
);
