#pragma once

#include <string>
#include <vector>

bool WriteResults(
    const std::string& path,
    const std::vector<long long>& counts,
    bool violation,
    std::string* error
);
