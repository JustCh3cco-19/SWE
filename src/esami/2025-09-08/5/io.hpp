#pragma once

#include <string>

bool WriteResults(
    const std::string& path,
    double rate,
    double v_value,
    double q_value,
    double cost,
    std::string* error
);
