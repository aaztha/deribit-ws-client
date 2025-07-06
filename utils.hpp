#pragma once

#include <nlohmann/json.hpp>
#include <fstream>

inline nlohmann::json load_config(const std::string& file_path) {
    std::ifstream file(file_path);
    if (!file) {
        throw std::runtime_error("Could not open config file");
    }
    nlohmann::json config;
    file >> config;
    return config;
}
