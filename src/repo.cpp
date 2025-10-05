//utils
#include "repo.h"
#include "utils.h"

//libs
#include <iostream>
#include <fstream>




fs::path getRepoPath() {
    return fs::current_path() / ".mgc";
}

fs::path getStagingPath() {
    return getRepoPath() / "staging";
}

fs::path getCommitsPath() {
    return getRepoPath() / "commits";
}

void initRepo() {
    fs::path repo_dir = getRepoPath();
    auto time_stamp = getCurrentTime();

    if(!fs::exists(repo_dir)) {
        fs::create_directories(getStagingPath());
        fs::create_directories(getCommitsPath());
        std::cout<< "Initialized empty repository at: " <<repo_dir<<"\n";
        std::ofstream log (repo_dir / "log.txt");
        log << "Repository Initialized: Location: "<< repo_dir << " - Time stamp: " << time_stamp << "\n";
    }
}

void showStatus() {
    fs::path cwd = fs::current_path();
    fs::path staging_dir = getStagingPath();

    std::cout << "=== Status ===\n";

    if(!fs::is_empty(staging_dir)) {
        std::cout << "Staged for commit: \n";
        for(auto& file : fs::directory_iterator(staging_dir)){
            std::cout << " " << file.path().filename().string() << "\n";
        }
    } else std::cout << "No staged files.\n";

    std::cout << "\nFiles in working directory:\n";
    for(auto& file : fs::directory_iterator(cwd)){
        if(file.path().filename() != ".mgc")
        std::cout << "  " << file.path().filename().string() << "\n";
    }
}

void showLogs() {

}