#include "LogEngine.hpp"
#include "QueryInterface.hpp"
#include <iostream>
#include <filesystem>

std::string getUniversalPath(const std::string& relativePath) {
    std::filesystem::path root(PROJECT_ROOT_DIR);
    return (root/relativePath).string();
}

int main() {
    LogEngine engine;
    engine.loadFromFile(getUniversalPath("logs.txt"));
    while(true) {
        std::string command;
        std::cout << "1) CHANGE - change file\n2) WRITE - write queries\n3) EXIT - exit program\nCommand: ";
        getline(std::cin, command);
        if("CHANGE" == command || "1" == command) {
            engine.clearLogs();
            std::cout << "Enter new path (or 'cancel'): ";
            std::string path;
            getline(std::cin, path);
            if("cancel" == path) continue;
            engine.loadFromFile(getUniversalPath(path));
        } else if ("WRITE" == command || "2" == command) {
            while(true) {
                std::cout << "Write your query (or 'cancel'): ";
                std::string query;
                getline(std::cin, query);
                if("cancel" == query) break;
                QueryInterface interface;
                QueryOptions opt = interface.parseQuery(query);
                std::vector<LogEntry> entries = engine.query(opt);
                for(const LogEntry& entry : entries) {
                    std::cout << entry << std::endl;
                }
            }
        } else if ("EXIT" == command || "3" == command) {
            return 0;
        }

    }
}