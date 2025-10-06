//utils
#include "hash.h"

//libs
#include <openssl/sha.h> // link openssl
#include <fstream>
#include <sstream>
#include <iomanip>

std::string hashFile(const std::string& filepath) {
    std::ifstream file(filepath, std::ios::binary);

    if(!file) return "";
    //create sha context and initialize it
    SHA_CTX ctx; //struct -> H0-H4
    SHA1_Init(&ctx); //sets defaults

    char buf[8192];
    while (file.read(buf, sizeof(buf))){
        SHA1_Update(&ctx, buf, file.gcount());
    }

    if(file.gcount() > 0){
        SHA1_Update(&ctx, buf, file.gcount());
    }

    unsigned char hash[SHA_DIGEST_LENGTH]; // final 20 byte hash
    // padding
    SHA1_Final(hash, &ctx);

    std::stringstream ss;

    for (int i = 0; i < SHA224_DIGEST_LENGTH; i++){
        // feeds hex values with constant width of 2 and padding 0 from the hash of i 
        // << writes to the stream
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i]; //i.e value = a -> + padding = 0a 
    }
    // returns complete hex parsed to string
    return ss.str();
}

