// utils
#include "repo.h"
#include "utils.h"

// libs
#include <iostream>
#include <fstream>

fs::path getRepoPath()
{
    return fs::current_path() / ".mgc";
}

fs::path getStagingPath()
{
    return getRepoPath() / "staging";
}

fs::path getCommitsPath()
{
    return getRepoPath() / "commits";
}

void initRepo()
{
    fs::path repo_dir = getRepoPath();
    auto time_stamp = getCurrentTime();

    if (!fs::exists(repo_dir))
    {
        fs::create_directories(getStagingPath());
        fs::create_directories(getCommitsPath());
        std::cout << "Initialized empty repository at: " << repo_dir << "\n";
        std::ofstream log(repo_dir / "log.txt");
        log << "Repository Initialized: Location: " << repo_dir << " - Time stamp: " << time_stamp << "\n";
    }
}

void showStatus()
{
    fs::path cwd = fs::current_path();
    fs::path staging_dir = getStagingPath();

    std::cout << "=== Status ===\n";

    if (!fs::is_empty(staging_dir))
    {
        std::cout << "Staged for commit: \n";
        for (auto &file : fs::directory_iterator(staging_dir))
        {
            std::cout << " " << file.path().filename().string() << "\n";
        }
    }
    else
        std::cout << "No staged files.\n";

    std::cout << "\nFiles in working directory:\n";
    for (auto &file : fs::directory_iterator(cwd))
    {
        if (file.path().filename() != ".mgc")
            std::cout << "  " << file.path().filename().string() << "\n";
    }
}

void showLogs()
{
    fs::path cwd = fs::current_path();
    fs::path repo_dir = getRepoPath();
    fs::path log_file = repo_dir / "log.txt";

    if (!fs::exists(repo_dir) || !fs::exists(log_file))
    {
        std::cout << "No repository found. Check directory or init a new repo using: mgc init.\n";
    }

    //if file & repo exist stream log.txt line by line
    std::ifstream log(log_file);
    std::string line;

    std::cout << "=== Repo Logs ===\n";
    while (std::getline(log, line))
    {
        std::cout << line << " \n";
    }
    
    log.close();
}

void branchRepo() {
    //get current branch state.

    //make a copy and branch trees

    //link to tree
}