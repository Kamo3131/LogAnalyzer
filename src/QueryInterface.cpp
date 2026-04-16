#include "QueryInterface.hpp"
#include "Utility.hpp"
#include <iostream>

QueryOptions QueryInterface::parseQuery(std::string line) {
    QueryOptions opt;
    opt.timeRange = createTimestamp(line);
    opt.level = createLevel(line);
    opt.source = createSource(line);
    opt.message = createMessage(line);
    return opt;
}
std::optional<std::pair<std::chrono::system_clock::time_point, std::chrono::system_clock::time_point>> QueryInterface::createTimestamp(std::string line) {
    std::regex timeRangeRegex(R"(TIMESTAMP\s+(?:from|od)\s+\"([^\"]+)\"\s+(?:to|do)\s+\"([^\"]+)\")");
    std::smatch match;
    
    if(std::regex_search(line, match, timeRangeRegex)) {
        std::pair<std::chrono::system_clock::time_point, std::chrono::system_clock::time_point> returnTimeRange;
        returnTimeRange.first = parseTimestamp(match[1].str());
        returnTimeRange.second = parseTimestamp(match[2].str());
        return returnTimeRange;
    }
    return std::nullopt;
}
std::optional<std::string> QueryInterface::createLevel(std::string line) {
    std::regex levelRegex(R"(LOG_LEVEL=\"([^\"]+)\")");
    std::smatch match;
    if(std::regex_search(line, match, levelRegex)) {
        std::string returnLevel;
        returnLevel = match[1].str();
        return returnLevel;
    }
    return std::nullopt;
}
std::optional<std::string> QueryInterface::createSource(std::string line) {
    std::regex sourceRegex(R"(SOURCE=\"([^\"]+)\")");
    std::smatch match;
    if(std::regex_search(line, match, sourceRegex)) {
        std::string returnSource;
        returnSource = match[1].str();
        return returnSource;
    }
    return std::nullopt;
}
std::optional<std::string> QueryInterface::createMessage(std::string line) {
    std::regex messageRegex(R"(Message=\"([^\"]+)\")");
    std::smatch match;
    if(std::regex_search(line, match, messageRegex)) {
        std::string returnMessage;
        returnMessage = match[1].str();
        return returnMessage;
    }
    return std::nullopt;
}