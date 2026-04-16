#pragma once
#include "QueryOptions.hpp"
#include <array>
#include <string>
#include <regex>

class QueryInterface {
        std::optional<std::pair<std::chrono::system_clock::time_point, std::chrono::system_clock::time_point>> createTimestamp(std::string timeRange);
        std::optional<std::string> createLevel(std::string level);
        std::optional<std::string> createSource(std::string source);
        std::optional<std::string> createMessage(std::string message);
    public:
        QueryOptions parseQuery(std::string line);
};