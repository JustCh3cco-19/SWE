#pragma once

#include <string>

bool WriteResults(
    const std::string& path,
    double rate,
    int suppliers,
    double cost,
    std::string* error
);
