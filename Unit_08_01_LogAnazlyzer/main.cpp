#include "LogAnalyzer.h"
#include <iostream>
#include <filesystem>
#include <thread>
#include <vector>
#include <format>

namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << std::format("Usage: {} <log_directory>\n", argv[0]);
        return 1;
    }

    std::string folderPath = argv[1];
    std::cout << std::format("CWD: {}\n", fs::current_path().string());
    std::cout << std::format("Analyzing folder: {}\n\n", folderPath);

    LogAnalyzer analyzer;
    std::vector<std::string> keywords = { "[WARN]", "[ERROR]", "[FATAL]", "[INFO]", "[DEBUG]", "[TRACE]" };
    std::vector<std::thread> threads;

    try {
        for (const auto& entry : fs::directory_iterator(folderPath)) {
            if (entry.is_regular_file() && entry.path().extension() == ".log") {
                threads.emplace_back(&LogAnalyzer::analyzeFile, &analyzer, entry.path().string(), keywords);
            }
        }
    }
    catch (const fs::filesystem_error& e) {
        std::cerr << std::format("Filesystem error: {}\n", e.what());
        return 1;
    }

    for (auto& t : threads) {
        if (t.joinable())
            t.join();
    }

    analyzer.printSummary();
    std::cout << std::format("Analysis complete. Processed {} files.\n", threads.size());

    return 0;
}