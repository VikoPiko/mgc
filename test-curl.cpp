#include <curl/curl.h>
#include <iostream>

#define CURL_STATICLIB

int main(){

    CURL *curl;
    CURLcode response;

    curl = curl_easy_init();

    std::ios::sync_with_stdio(false);
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    if(curl){
        curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:3000/hello");

        response = curl_easy_perform(curl);

        if(response != CURLE_OK){
            std::cout << "Error: " << curl_easy_strerror(response) << "\n";
        }
    }

    //always clean up
    curl_easy_cleanup(curl);

    return 0;
}