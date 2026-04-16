#include <gtest/gtest.h>
#include <chrono>
#include <optional>
#include <vector>
#include "LogEntry.hpp"
#include "LogEngine.hpp"
#include "QueryInterface.hpp"
#include "Utility.hpp"

TEST(QueryInterfaceTest, ShouldExtractLogLevelCorrectly) {
    QueryInterface interface;
    std::string query = "LOG_LEVEL=\"ERROR\"";
    
    auto opts = interface.parseQuery(query);
    
    ASSERT_TRUE(opts.level.has_value());
    EXPECT_EQ(opts.level.value(), "ERROR");
}

TEST(QueryInterfaceTest, ShouldReturnNulloptWhenTimeRangeMissing) {
    QueryInterface interface;
    std::string query = "SOURCE=\"Database\"";
    
    auto opts = interface.parseQuery(query);
    
    EXPECT_EQ(opts.timeRange, std::nullopt);
    EXPECT_FALSE(opts.timeRange.has_value());
}

TEST(QueryInterfaceTest, ShouldExtractFullTimeRange) {
    QueryInterface interface;
    std::string query = "TIMESTAMP from \"2023-10-25T10:00:00\" to \"2023-10-25T10:10:00\"";
    
    auto opts = interface.parseQuery(query);
    
    ASSERT_TRUE(opts.timeRange.has_value());
    EXPECT_EQ(opts.timeRange->first, parseTimestamp("2023-10-25T10:00:00"));
    EXPECT_EQ(opts.timeRange->second, parseTimestamp("2023-10-25T10:10:00"));
}

TEST(QueryInterfaceTest, ShouldHandlePartialMessageSearch) {
    QueryInterface interface;
    std::string query = "Message=\"Transaction rejected\"";
    
    auto opts = interface.parseQuery(query);
    
    ASSERT_TRUE(opts.message.has_value());
    EXPECT_EQ(opts.message.value(), "Transaction rejected");
}

class LogEngineTest : public ::testing::Test {
protected:
    LogEngine engine;

    void SetUp() override {
        LogEntry e1{parseTimestamp("2023-10-25T10:00:00"), "INFO", "AuthService", "User logged in"};
        LogEntry e2{parseTimestamp("2023-10-25T10:05:00"), "ERROR", "Database", "Connection timeout"};
        LogEntry e3{parseTimestamp("2023-10-25T10:10:00"), "ERROR", "Payment", "Transaction rejected"};
        
        engine.addEntry(e1);
        engine.addEntry(e2);
        engine.addEntry(e3);
    }
};

TEST_F(LogEngineTest, FilterByMultipleCriteriaAND) {
    QueryOptions opts;
    opts.level = "ERROR";
    opts.message = "Transaction";
    
    auto results = engine.query(opts);
    ASSERT_EQ(results.size(), 1);
    EXPECT_EQ(results[0].source, "Payment");
}

TEST_F(LogEngineTest, FilterByTimeRangeOnly) {
    QueryOptions opts;
    opts.timeRange = std::make_pair(
        parseTimestamp("2023-10-25T09:00:00"),
        parseTimestamp("2023-10-25T10:07:00")
    );

    
    auto results = engine.query(opts);
    
    EXPECT_EQ(results.size(), 2);
}

TEST_F(LogEngineTest, ReturnAllWhenNoFiltersApplied) {
    QueryOptions emptyOpts;
    auto results = engine.query(emptyOpts);
    
    EXPECT_EQ(results.size(), 3);
}

TEST_F(LogEngineTest, ReturnEmptyWhenNoMatches) {
    QueryOptions opts;
    opts.source = "NonExistent";
    
    auto results = engine.query(opts);
    
    EXPECT_TRUE(results.empty());
}