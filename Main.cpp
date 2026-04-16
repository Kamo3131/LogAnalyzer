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
        std::cout << "Write your query: ";
        std::string query;
        getline(std::cin, query);
        QueryInterface interface;
        QueryOptions opt = interface.parseQuery(query);
        std::vector<LogEntry> entries = engine.query(opt);
        for(const LogEntry& entry : entries) {
            std::cout << entry << std::endl;
        }
    }

}