#include <iostream>
#include <curl/curl.h>
#include <string>
#include <sstream>
#include <unordered_map>

// Estructura para almacenar el cuerpo de la respuesta
struct ResponseData
{
    std::string body;
};

// Función de escritura personalizada para capturar el cuerpo de la respuesta
size_t WriteCallback(void *contents, size_t size, size_t nmemb, ResponseData *responseData)
{
    size_t totalSize = size * nmemb;
    responseData->body.append((char *)contents, totalSize);
    return totalSize;
}

// Función para extraer el valor de un campo específico del cuerpo JSON de la respuesta
std::string extractField(const std::string &responseBody, const std::string &fieldName)
{
    std::istringstream ss(responseBody);
    std::string line;
    std::unordered_map<std::string, std::string> fields;

    // Leer línea por línea y buscar el campo especificado
    while (std::getline(ss, line))
    {
        // Buscar el nombre del campo
        size_t pos = line.find("\"" + fieldName + "\"");
        if (pos != std::string::npos)
        {
            // Buscar el valor asociado
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

    // Si no se encontró el campo, devolver una cadena vacía
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
        // Configuración para capturar el cuerpo de la respuesta
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
