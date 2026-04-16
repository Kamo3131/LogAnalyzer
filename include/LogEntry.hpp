#pragma once
#include <string>
#include <chrono>
#include <iostream>
struct LogEntry {
    std::chrono::system_clock::time_point timestamp;
    std::string level;
    std::string source;
    std::string message;
    

};

    inline std::ostream& operator<<(std::ostream& os, const LogEntry& entry) {
        std::time_t tt = std::chrono::system_clock::to_time_t(entry.timestamp);
        std::tm tm = *std::gmtime(&tt);
        os << "[" << std::put_time(&tm, "%Y-%m-%dT%H:%M:%S") << "] [" << entry.level << "] [" << entry.source << "] " << entry.message;
        return os; 
    }