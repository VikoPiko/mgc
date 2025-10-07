#include "commit.h"
#include "repo.h"
#include "utils.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <chrono>
#include <iomanip>
#include <vector>

namespace fs = std::filesystem;

void commitChanges(const std::string &message)
{
    fs::path staging_dir = getStagingPath();
    fs::path commit_dir = getCommitsPath();
    auto time_stamp = getCurrentTime();

    if (!fs::exists(staging_dir) || fs::is_empty(staging_dir))
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

    std::vector<std::string> committed_files;

    // Copy all files recursively from staging!
    for (auto it = fs::recursive_directory_iterator(staging_dir); it != fs::recursive_directory_iterator(); ++it)
    {
        const auto &path = it->path();
        fs::path rel_path = fs::relative(path, staging_dir);
        fs::path dest = new_commit / rel_path;

        if (fs::is_directory(path))
        {
            fs::create_directories(dest);
            continue;
        }

        if (fs::is_regular_file(path))
        {
            fs::create_directories(dest.parent_path());
            fs::copy_file(path, dest, fs::copy_options::overwrite_existing);
            committed_files.push_back(rel_path.string());
        }
    }
    // added logging commited files/folders to log.txt for readibility.
    std::ofstream log(getRepoPath() / "log.txt", std::ios::app);
    log << "Commit " << folder_name.str() << ": " << message << "\t Created at: " << time_stamp << "\n";

    for (const auto &file : committed_files)
        log << "  - " << file << "\n";

    log << "------------------------------------------------------------\n";

    // clean up after commit
    fs::remove_all(staging_dir);
    fs::create_directories(staging_dir);

    std::cout << "Committed " << committed_files.size() << " file(s) with message: " << message << "\n";
}