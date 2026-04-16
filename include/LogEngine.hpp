#pragma once
#include <algorithm>
#include <vector>
#include "QueryOptions.hpp"
#include "LogEntry.hpp"
#include <iostream>
#include <fstream>
#include <regex>
#include <ctime>
class LogEngine {
    private:
        std::vector<LogEntry> logs;
    public:
        void loadFromFile(const std::string& path);
        void addEntry(const LogEntry & entry);
        std::vector<LogEntry> query(const QueryOptions& opts);
        [[nodiscard]] bool isInRange(std::chrono::system_clock::time_point timePoint, 
            std::optional<std::pair<std::chrono::system_clock::time_point, std::chrono::system_clock::time_point>> timeRange) const;
};