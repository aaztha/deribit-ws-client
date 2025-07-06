#include "rest_api.hpp"
#include <cpr/cpr.h>
#include <iostream>

using json = nlohmann::json;

std::string authenticate(const json& config) {
    /*
    auto response = cpr::Post(
        cpr::Url{"https://test.deribit.com/api/v2/public/auth"},
        cpr::Payload{
            {"grant_type", "client_credentials"},
            {"client_id", config["client_id"].get<std::string>()},
            {"client_secret", config["client_secret"].get<std::string>()}
        }

    );
    */

    json payload = {
       {"jsonrpc", "2.0"},
       {"id", 1},
       {"method", "public/auth"},
       {"params", {
           {"grant_type", "client_credentials"},
           {"client_id", config["client_id"].get<std::string>()},
           {"client_secret", config["client_secret"].get<std::string>()}
       }}
    };

    auto response = cpr::Post(
        cpr::Url{ "https://test.deribit.com/api/v2/public/auth" },
        cpr::Header{ {"Content-Type", "application/json"} },
        cpr::Body{ payload.dump() }
    );

    if (response.status_code != 200) {
        throw std::runtime_error("Auth failed: " + response.text);
    }

    auto j = json::parse(response.text);
    return j["result"]["access_token"];
}

std::vector<std::string> fetch_option_instruments(const json& config, const std::string& token) {
    auto response = cpr::Get(
        cpr::Url{"https://test.deribit.com/api/v2/public/get_instruments"},
        cpr::Parameters{{"currency", "BTC"}, {"kind", "option"}}
    );

    if (response.status_code != 200) {
        throw std::runtime_error("Fetching instruments failed: " + response.text);
    }

    auto j = json::parse(response.text);
    std::vector<std::string> filtered;
    for (const auto& instrument : j["result"]) {
        std::string name = instrument["instrument_name"];
        std::cout << name << std::endl;
        if (name.find(config["expiry_date"].get<std::string>()) != std::string::npos) {
            filtered.push_back(name);
        }
    }
    return filtered;
}
