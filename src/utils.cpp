#include "utils.h"

#include <ctime>
#include <iomanip>
#include <sstream>
#include <chrono>
#include <iostream>

// gets current time to use as a timestamp for events
std::string getCurrentTime()
{
    auto now = std::chrono::system_clock::now(); // get current time as a time point

    std::time_t current_time = std::chrono::system_clock::to_time_t(now); // convert it for better formatting

    std::tm *tm_ptr = std::localtime(&current_time); // tm struct

    std::ostringstream oss;
    oss << std::put_time(tm_ptr, "%Y-%m-%d %H:%M:%S");

    return oss.str();
}

void showHelp()
{
    std::cout << "\n\t===================================== MGC - Mini Git Clone CLI =====================================\n\n";
    std::cout << "Usage:\n";
    std::cout << "  mgc <command> [options]\n\n";
    std::cout << "Commands:\n";
    std::cout << "  init                  Create a new repository in the current directory.\n";
    std::cout << "  status                Show status of files (Staged, Committed, or Untracked).\n";
    std::cout << "  log                   Show commit history.\n";
    std::cout << "  add <file|.>          Stage a file or all files (use '.' for all, recursive).\n";
    std::cout << "  commit <message>      Commit all staged files with a message -> needs to be passed as string -> \"<message>\" \n\n";
    std::cout << "Options:\n";
    std::cout << "  -h, --help            Show this help message.\n\n";
    std::cout << "Examples:\n";
    std::cout << "  mgc init\n";
    std::cout << "  mgc add test.txt\n";
    std::cout << "  mgc add .\n";
    std::cout << "  mgc commit \"Initial commit\"\n";
    std::cout << "  mgc status\n";
    std::cout << "  mgc log\n\n";
}