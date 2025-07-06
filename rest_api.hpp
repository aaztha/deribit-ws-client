#pragma once

#include <string>
#include <vector>
#include <nlohmann/json.hpp>

std::string authenticate(const nlohmann::json& config);
std::vector<std::string> fetch_option_instruments(const nlohmann::json& config, const std::string& token);
