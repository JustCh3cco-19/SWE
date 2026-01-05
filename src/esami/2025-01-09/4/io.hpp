#pragma once

#include <string>
#include <vector>

bool WriteResults(
    const std::string& path,
    const std::vector<long long>& counts,
    long long total_messages,
    std::string* error
);
