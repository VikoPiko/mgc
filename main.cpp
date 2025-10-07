#include "repo.h"
#include "commit.h"
#include "staging.h"
#include "utils.h"
#include "req-handler.h"

#include <iostream>

// takes in arg counter and arg vector as params
// mgc - argv[0], <command> argv[1], [args] argv[2...n]

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cout << "\n=============================================================\n";
        std::cout << "\n               Usage: mgc <command> [args]\n";
        std::cout << "\nTo see available commands run: mgc help || mgc -h || mgc --help\n";
        std::cout << "\n=============================================================\n\n";
        return 1;
    }

    std::string command = argv[1];

    if (argc >= 4)
    {
        std::cout << "Too many arguments passed. Run mgc --help to see usage.\n";
        return -1;
    }

    if (command == "init")
        initRepo();
    else if (command == "status")
        showStatus();
    else if (command == "log")
        showLogs();
    else if (command == "add")
    {
        addFile(argv[2]);
    }
    else if (command == "test")
    {
        std::cout << "Running testRequest()...\n";
        testRequest();
    }
    else if (command == "commit")
    {
        if (argc < 3 || argv[2] == nullptr || std::string(argv[2]).empty())
        {
            std::cout << "\n❌ Cannot commit without a message.\n";
            std::cout << "Usage: mgc commit \"Your commit message\"\n";
            return -1;
        }

        commitChanges(argv[2]);
    }
    else if (command == "help" || command == "--help" || command == "-h")
        showHelp();
    else
    {
        std::cout << "Unknown command: " << command << "\n";
        std::cout << "To see available commands run: mgc help || mgc -h || mgc --help\n";
    }
}