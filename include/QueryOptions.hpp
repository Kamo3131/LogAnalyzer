#pragma once
#include <string>
#include <optional>
#include <utility>
#include <chrono>
struct QueryOptions {
    std::optional<std::pair<std::chrono::system_clock::time_point, std::chrono::system_clock::time_point>> timeRange;
    std::optional<std::string> level;
    std::optional<std::string> source;
    std::optional<std::string> message;
};