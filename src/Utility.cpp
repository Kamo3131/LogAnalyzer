#include "Utility.hpp"

std::chrono::system_clock::time_point parseTimestamp(const std::string& tsStr) {
    std::tm tm = {};
    std::stringstream ss(tsStr);
    ss >> std::get_time(&tm, "%Y-%m-%dT%H:%M:%S");
    return std::chrono::system_clock::from_time_t(std::mktime(&tm));
}