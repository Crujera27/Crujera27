#include <iostream>
#include "http_request.hpp" // Incluye el archivo con las definiciones y funciones


int main()
{
    // Realizar la solicitud HTTP
    std::cout << "Pon un pokemon: ";
    std::string pokemon;
    std::cin >> pokemon;
     std::string responseData = performHttpRequest("https://pokeapi.co/api/v2/pokemon/" + pokemon);

    // Extraer el valor de diferentes campos del cuerpo JSON de la respuesta
    std::string abilities = extractField(responseData, "abilities");
    std::string moves = extractField(responseData, "moves");
    std::string types = extractField(responseData, "types");
    std::string stats = extractField(responseData, "stats");

    // Imprimir los valores extraídos
    std::cout << "abilities: " << abilities << std::endl;
    std::cout << "moves: " << moves << std::endl;
    std::cout << "types: " << types << std::endl;
    std::cout << "stats: " << stats << std::endl;

    return 0;
}
