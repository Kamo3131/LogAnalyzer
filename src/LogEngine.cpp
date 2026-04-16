    #include <LogEngine.hpp> 
    #include "Utility.hpp"  
    void LogEngine::loadFromFile(const std::string& path) {
        std::ifstream file(path);
        if (!file.is_open()) {
            throw std::runtime_error("Cannot open file on path: " + path);
        }
        std::string line;
        std::regex logPattern(R"(^\[([^\]]+)\]\s+\[([^\]]+)\]\s+\[([^\]]+)\]\s+(.*)$)");
        std::smatch match;

        while (getline(file, line)) {
            if (std::regex_search(line, match, logPattern)) {
                LogEntry entry;

                entry.timestamp = parseTimestamp(match[1].str());

                entry.level = match[2].str();
                entry.source = match[3].str();
                entry.message = match[4].str();

                logs.push_back(entry);
            } else {
                std::cerr << "Wrong line skipped: " << line << std::endl; 
            }
        }
        file.close();
    }
    void LogEngine::clearLogs() {
        logs.clear();
    }
    bool LogEngine::isInRange(std::chrono::system_clock::time_point timePoint, 
        std::optional<std::pair<std::chrono::system_clock::time_point, std::chrono::system_clock::time_point>> timeRange) const {
            if(timeRange->first <= timePoint && timeRange->second >= timePoint) {
                return true;
            }
            return false;
    }
    std::vector<LogEntry> LogEngine::query(const QueryOptions& opts) {
        std::vector<LogEntry> results;
        std::copy_if(logs.begin(), logs.end(), std::back_inserter(results), [&](const LogEntry& e) {
            if (opts.level && e.level != *opts.level) return false;
            if (opts.source && e.source != *opts.source) return false;
            if (opts.message && e.message.find(*opts.message) == std::string::npos) return false;
            if (opts.timeRange && !isInRange(e.timestamp, *opts.timeRange)) return false;
            return true;
        });
        return results;
    }

    void LogEngine::addEntry(const LogEntry & entry) {
        logs.push_back(entry);
    }