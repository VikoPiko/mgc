#pragma once
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

fs::path getRepoPath();
fs::path getStagingPath();
fs::path getCommitsPath();

void initRepo();
void branchRepo();
void showStatus();
void showLogs();