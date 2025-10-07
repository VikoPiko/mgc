#define CURL_STATICLIB

#include <curl/curl.h>
#include <iostream>
#include <string>

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
    size_t totalSize = size * nmemb;
    std::string* str = (std::string*)userp;
    str->append((char*)contents, totalSize);
    return totalSize;
}

void testRequest()
{
    CURL* curl = curl_easy_init();
    if (!curl)
    {
        std::cerr << "Failed to initialize curl\n";
        return;
    }

    std::string response;

    curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:3000/hello");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
    curl_easy_setopt(curl, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_1_1);

    CURLcode res = curl_easy_perform(curl);
    std::cout << "CURLcode: " << res << "\n";
    
    if (res != CURLE_OK)
    {
        std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << "\n";
    }
    else
    {
        std::cout << "Response: " << response << "\n";
    }

    curl_easy_cleanup(curl);
}
