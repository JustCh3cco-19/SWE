#pragma once

#include <string>

bool WriteResults(
    const std::string& path,
    double avg,
    double stddev,
    std::string* error
);
