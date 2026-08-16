#pragma once

#include <string>

#include <mocc/exam_utils.hpp>

bool LoadParameters(const std::string& path, mocc_utils::MdpData*out, std::string*error);
