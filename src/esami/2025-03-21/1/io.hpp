#pragma once

#include <string>

bool WriteResults(
    const std::string& path,
    int active,
    int total,
    std::string* error
);
