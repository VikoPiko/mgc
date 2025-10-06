#include <unordered_map>

std::unordered_map<std::string, std::string> loadHashes();
void saveHashes(const std::unordered_map<std::string, std::string> &hashes);