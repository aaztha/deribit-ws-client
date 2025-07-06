#pragma once

#include <nlohmann/json.hpp>
#include <sqlite3.h>
#include <vector>
#include <string>

void subscribe_to_ws(const std::vector<std::string>& instruments, const nlohmann::json& config, sqlite3* db);
