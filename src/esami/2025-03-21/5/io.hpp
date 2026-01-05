#pragma once

#include <string>

bool WriteResults(
    const std::string& path,
    double alpha,
    double w_rate,
    double s_rate,
    double j_value,
    std::string* error
);
