#include "Utility.hpp"

std::chrono::system_clock::time_point parseTimestamp(const std::string& tsStr) {
    std::tm tm = {};
    std::istringstream ss(tsStr);
    ss >> std::get_time(&tm, "%Y-%m-%dT%H:%M:%S");

    if (ss.fail()) {
        return std::chrono::system_clock::time_point::min();
    }
    tm.tm_isdst = 0; 
    time_t tt = _mkgmtime(&tm);
    
    return std::chrono::system_clock::from_time_t(tt);
}