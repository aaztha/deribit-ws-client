#include "rest_api.hpp"
#include "ws_client.hpp"
#include "db_handler.hpp"
#include "utils.hpp"
#include <iostream>
#include <sqlite3.h>

int main() {
    try {
        std::cout << "Starting Deribit client..." << std::endl;

        auto config = load_config("config.json");

        std::string token = authenticate(config);
        std::cout << "Authenticated.\n";

        //auto instruments = fetch_option_instruments(config, token); //for all instruments-not needed rn
        
        //for 5 instruments:
        auto all_instruments = fetch_option_instruments(config, token);
        std::vector<std::string> instruments;
        int limit = std::min(5, (int)all_instruments.size());
        for (int i = 0; i < limit; ++i) {
            instruments.push_back(all_instruments[i]);
        }

        if (all_instruments.empty()) {
            throw std::runtime_error("No instruments found for the specified expiry date.");
		}
        std::cout << "Fetched instruments: " << instruments.size() << std::endl;

        sqlite3* db = nullptr;
        init_db(&db);

        subscribe_to_ws(instruments, config, db);

        sqlite3_close(db);

    } catch (const std::exception& e) {
        std::cerr << "[Error] " << e.what() << std::endl;
    }
    return 0;
}
