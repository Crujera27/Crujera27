#include <iostream>
#include <curl/curl.h>
#include <string>
#include <sstream>
#include <unordered_map>
struct ResponseData
{
    std::string body;
};
size_t WriteCallback(void *contents, size_t size, size_t nmemb, ResponseData *responseData)
{
    size_t totalSize = size * nmemb;
    responseData->body.append((char *)contents, totalSize);
    return totalSize;
}
std::string extractField(const std::string &responseBody, const std::string &fieldName)
{
    std::istringstream ss(responseBody);
    std::string line;
    std::unordered_map<std::string, std::string> fields;
    while (std::getline(ss, line))
    {
        size_t pos = line.find("\"" + fieldName + "\"");
        if (pos != std::string::npos)
        {
            pos = line.find(":", pos);
            if (pos != std::string::npos)
            {
                size_t start = line.find_first_of("\"", pos);
                size_t end = line.find_last_of("\"");
                if (start != std::string::npos && end != std::string::npos && start < end)
                {
                    return line.substr(start + 1, end - start - 1);
                }
            }
        }
    }
    return "";
}

std::string performHttpRequest(const std::string &url)
{
    CURL *curl;
    CURLcode res;
    ResponseData responseData;

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseData);
        res = curl_easy_perform(curl);
        if (res != CURLE_OK)
        {
            std::cerr << "Error en la solicitud: " << curl_easy_strerror(res) << std::endl;
        }
        curl_easy_cleanup(curl);
    }
    else
    {
        std::cerr << "Error inicializando curl." << std::endl;
    }
    curl_global_cleanup();
    return responseData.body;
}
