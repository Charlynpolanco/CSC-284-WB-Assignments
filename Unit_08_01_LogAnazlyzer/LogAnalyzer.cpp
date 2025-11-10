#include "LogAnalyzer.h"
#include <fstream>
#include <iostream>
#include <string>
#include <format>

void LogAnalyzer::analyzeFile(const std::string& filename, const std::vector<std::string>& keywords) {
    std::ifstream file(filename);
    if (!file) {
        std::lock_guard<std::mutex> lock(printMutex);
        std::cerr << std::format("Error: Could not open file {}\n", filename);
        return;
    }

    {
        std::lock_guard<std::mutex> lock(printMutex);
        std::cout << std::format("Processing: {}\n", filename);
    }

    std::string line;
    while (std::getline(file, line)) {
        for (const auto& keyword : keywords) {
            if (line.find(keyword) != std::string::npos) {
                std::lock_guard<std::mutex> lock(countMutex);
                keywordCounts[keyword]++;
            }
        }
    }
}

void LogAnalyzer::printSummary() const {
    std::lock_guard<std::mutex> lock(printMutex);

    std::cout << "\n--- Keyword Summary ---\n";

    
    std::vector<std::string> order = { "[WARN]", "[ERROR]", "[FATAL]", "[INFO]", "[DEBUG]", "[TRACE]" };

    for (const auto& key : order) {
        int count = 0;
        {
            std::lock_guard<std::mutex> countLock(countMutex);
            auto it = keywordCounts.find(key);
            if (it != keywordCounts.end()) count = it->second;
        }

        std::string displayKey = key.substr(1, key.size() - 2);
        std::cout << displayKey << ": " << count << "\n";
    }

    std::cout << "-----------------------\n";
}