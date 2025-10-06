// utils
#include "staging.h"
#include "repo.h"

// libs
#include <vector>
#include <iostream>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

std::vector<std::string> getIgnoredPatterns()
{
    std::vector<std::string> ignored; // vector to store ignored files

    fs::path ignore_file = fs::current_path() / ".mgcignore";
    if (fs::exists(ignore_file))
    {
        std::ifstream in(ignore_file);
        std::string line;
        while (std::getline(in, line))
        {
            auto s = line.find_first_not_of(" \t\r\n");
            if (s == std::string::npos)
                continue;
            auto e = line.find_last_not_of(" \t\r\n");
            std::string pattern = line.substr(s, e - s + 1);

            if (pattern.empty() || pattern[0] == '#')
                continue;
            ignored.push_back(pattern);
        }
    }
    return ignored;
}

bool isIgnored(const fs::path &file, const std::vector<std::string> &ignored)
{
    std::string relative = fs::relative(file, fs::current_path()).string();

    for (const auto &pattern : ignored)
    {
        if (!pattern.empty() && pattern.back() == '/')
        {
            if (relative.rfind(pattern.substr(0, pattern.size() - 1), 0) == 0)
                return true;
        }
        if (relative.find(pattern) != std::string::npos)
            return true;
    }
    return false;
}

void addFile(const std::string &filename)
{
    fs::path cwd = fs::current_path();
    fs::path staging_dir = getStagingPath();
    auto ignored = getIgnoredPatterns();

    if (filename == ".")
    {
        for (auto &f : fs::recursive_directory_iterator(cwd))
        {
            if (isIgnored(f.path(), ignored) || !fs::is_regular_file(f.path()))
                continue;

            fs::path dest = staging_dir / fs::relative(f.path(), cwd);
            fs::create_directories(dest.parent_path());

            // copy only if there are changes
            if (!fs::exists(dest) || fs::file_size(dest) != fs::file_size(f.path()))
            {
                fs::copy_file(f.path(), dest, fs::copy_options::overwrite_existing);
                std::cout << "Added " << fs::relative(f.path(), cwd).string() << ".\n";
            }
        }
        std::cout << "All files are staged!\n";
        return;
    }

    fs::path file_to_add = cwd / filename;

    if (!fs::exists(file_to_add))
    {
        std::cout << "File does not exist.\n";
    }

    fs::path dest = staging_dir / filename;
    fs::create_directories(dest.parent_path());
    fs::copy_file(file_to_add, dest, fs::copy_options::overwrite_existing);

    std::cout << "Staged " << filename << "successfully.\n";
}
