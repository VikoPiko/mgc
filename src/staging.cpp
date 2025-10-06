// utils
#include "staging.h"
#include "repo.h"
#include "hash.h"
#include "hash_utils.h"

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

    auto index = loadHashes(); // load current hashes
    bool any_added = false;

    if (filename == ".")
    {
        for (auto &f : fs::recursive_directory_iterator(cwd))
        {
            if (isIgnored(f.path(), ignored) || !fs::is_regular_file(f.path()))
                continue;

            std::string rel_path = fs::relative(f.path(), cwd).string();
            std::string new_hash = hashFile(f.path().string());

            if (index[rel_path] != new_hash)
            {
                fs::path dest = staging_dir / rel_path;
                fs::create_directories(dest.parent_path());
                fs::copy_file(f.path(), dest, fs::copy_options::overwrite_existing);

                index[rel_path] = new_hash;
                std::cout << "Staged: " << rel_path << "\n";
                any_added = true;
            }
        }

        if (!any_added)
        {
            std::cout << "No changes detected - nothing to stage.\n";
        }
        else
        {
            saveHashes(index);
            std::cout << "All changed files are staged!\n";
        }
        return;
    }

    // Handle single file case
    fs::path file_to_add = cwd / filename;
    if (!fs::exists(file_to_add))
    {
        std::cout << "File does not exist.\n";
        return;
    }

    std::string rel_path = filename;
    std::string new_hash = hashFile(file_to_add.string());

    if (index[rel_path] != new_hash)
    {
        fs::path dest = staging_dir / rel_path;
        fs::create_directories(dest.parent_path());
        fs::copy_file(file_to_add, dest, fs::copy_options::overwrite_existing);
        index[rel_path] = new_hash;

        std::cout << "Staged: " << rel_path << "\n";
        saveHashes(index);
    }
    else
    {
        std::cout << "No changes in " << rel_path << ".\n";
    }
}