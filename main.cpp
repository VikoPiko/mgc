#include "repo.h"

#include <iostream>

// takes in arg counter and arg vector as params
// mgc - argv[0], <command> argv[1], [args] argv[2...n]

int main(int argc, char* argv[]) {
    if(argc < 2) {
        std::cout << "Usage: mygit <command> [args]\n";
        return 1;
    }

    std::string command = argv[1];

    if(command == "init") initRepo();
    else if(command == "status") showStatus();
    else {
         std::cout << "Unknown command: " << command << "\n";
         std::cout << "To see available commands run:   mgc help\n";
    }
}