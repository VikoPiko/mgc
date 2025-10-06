#include "commit.h"
#include "repo.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <chrono>
#include <iomanip>

namespace fs = std::filesystem;

void commitChanges(const std::string &message)
{
    fs::path staging_dir = getStagingPath();
    fs::path commit_dir = getCommitsPath();

    if (fs::is_empty(staging_dir))
    {
        std::cout << "Nothing to commit.\n";
        return;
    }

    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::stringstream folder_name;
    folder_name << std::put_time(std::localtime(&now_time), "%Y%m%d_%H%M%S");

    fs::path new_commit = commit_dir / folder_name.str();
    fs::create_directory(new_commit);

    for (auto &f : fs::directory_iterator(staging_dir))
        fs::copy(f.path(), new_commit / f.path().filename(), fs::copy_options::overwrite_existing);

    std::ofstream log(getRepoPath() / "log.txt", std::ios::app);
    log << "Commit " << folder_name.str() << ": " << message << "\n";

    for (auto &f : fs::directory_iterator(staging_dir))
        fs::remove_all(f.path());

    std::cout << "Committed changes with message: " << message << "\n";
}
