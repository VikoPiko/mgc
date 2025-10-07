//utils
#include "hash.h"

//libs
// #include <openssl/sha.h> // link openssl --> DEPRECIATED USE EVP INSTEAD
#include <openssl/evp.h> // link openssl after 3.0 migration
#include <fstream>
#include <sstream>
#include <iomanip>

std::string hashFile(const std::string& filepath) {
    std::ifstream file(filepath, std::ios::binary);

    if(!file) return "";
    //create sha context and initialize it
    EVP_MD_CTX* ctx = EVP_MD_CTX_new();
    if (!ctx)
        return ""; //struct -> H0-H4
    // SHA1_Init(&ctx); //sets defaults

      if (EVP_DigestInit_ex(ctx, EVP_sha1(), nullptr) != 1) {
        EVP_MD_CTX_free(ctx);
        return "";
    }

    char buf[8192];
    while (file.good()){
        // SHA1_Update(&ctx, buf, file.gcount());
        file.read(buf, sizeof(buf));
        std::streamsize bytesRead = file.gcount();
        if(bytesRead > 0)
            EVP_DigestUpdate(ctx, buf, bytesRead);
    }

    unsigned char hash[EVP_MAX_MD_SIZE]; // final 20 byte hash
    unsigned int hash_len = 0;

    // padding
     if (EVP_DigestFinal_ex(ctx, hash, &hash_len) != 1) {
        EVP_MD_CTX_free(ctx);
        return "";
    }

    EVP_MD_CTX_free(ctx);

    // feeds hex values with constant width of 2 and padding 0 from the hash of i 
    // << writes to the stream
    //i.e value = a -> + padding = 0a 
   std::ostringstream ss;
    ss << std::hex << std::setfill('0');
    for (unsigned int i = 0; i < hash_len; i++)
        ss << std::setw(2) << static_cast<int>(hash[i]);

    return ss.str();
}

