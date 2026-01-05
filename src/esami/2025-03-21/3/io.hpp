#pragma once

#include <string>

bool WriteResults(
    const std::string& path,
    double oversellings,
    int num_servers,
    int horizon,
    std::string* error
);
