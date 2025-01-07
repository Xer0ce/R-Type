/*
** EPITECH PROJECT, 2025
** RType
** File description:
** Wave
*/

#include <fstream>
#include "json/include/nlohmann/json.hpp"
#include "Wave.hpp"

void Wave::load(std::string path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Impossible d'ouvrir le fichier : " + path);
    }

    nlohmann::json j;
    file >> j;

    file.close();
};