#include <unordered_map>
#include <fstream>
#include <sstream>

std::unordered_map<std::string, std::string> loadHashes() {
    std::unordered_map<std::string, std::string> hashes;
    std::ifstream in(".mgc/index.txt");
    std::string path, hash;

    while(in >> path >> hash){
        hashes[path] = hash;
    }
    return hashes;
}

void saveHashes(const std::unordered_map<std::string, std::string> &hashes){
    std::ofstream out(".mgc/index.txt", std::ios::trunc);
    for (const auto &p : hashes){
        out << p.first << " " << p.second <<  "\n";
    }
}