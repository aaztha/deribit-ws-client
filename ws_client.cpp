#include "ws_client.hpp"
#include "db_handler.hpp"
#include <ixwebsocket/IXWebSocket.h>
#include <iostream>

using json = nlohmann::json;

void subscribe_to_ws(const std::vector<std::string>& instruments, const json& config, sqlite3* db) {
    ix::WebSocket ws;
    ws.setUrl("wss://test.deribit.com/ws/api/v2");

    ws.setOnMessageCallback([db](const ix::WebSocketMessagePtr& msg) {
        if (msg->type == ix::WebSocketMessageType::Message) {
            if (msg->str.empty()) {
                std::cerr << "Received empty message." << std::endl;
                return;
			}
            std::cout << "Raw message: " << msg->str << std::endl;

			// Parse the JSON message
            auto j = json::parse(msg->str);

            if (j.contains("params") && j["params"].contains("data")) {
                auto data = j["params"]["data"];
                std::string instrument = data["instrument_name"];
                double price = data["last_price"];
                double delta = data["greeks"]["delta"];
                double volatility = data["greeks"]["iv"];
                int64_t timestamp = data["timestamp"];

                insert_ticker_data(db, instrument, price, delta, volatility, timestamp);
                std::cout << "Inserted: " << instrument << " " << price << std::endl;
            }
        }
        else if (msg->type == ix::WebSocketMessageType::Open) {
            std::cout << "WebSocket connection opened." << std::endl;
        }
        else if (msg->type == ix::WebSocketMessageType::Close) {
            std::cout << "WebSocket connection closed." << std::endl;
        }
        else if (msg->type == ix::WebSocketMessageType::Error) {
            std::cerr << "WebSocket error: " << msg->errorInfo.reason << std::endl;
		}
    });

    for (const auto& i : instruments) {
        std::cout << "Subscribing to: ticker." << i << ".raw" << std::endl;
    }


    ws.start();

    //Removing cuz WebSocket endpoint does not accept this REST-style auth
    // Auth
    //json auth = {
    //    {"jsonrpc", "2.0"},
    //    {"id", 1},
    //    {"method", "public/auth"},
    //    {"params", {
    //        {"grant_type", "client_credentials"},
    //        {"client_id", config["client_id"]},
    //        {"client_secret", config["client_secret"]}
    //    }}
    //};
    //ws.send(auth.dump());

    // Subscribe
    json sub = {
        {"jsonrpc", "2.0"},
        {"id", 2},
        {"method", "subscribe"},
        {"params", {{"channels", {}}}}
    };
    for (const auto& i : instruments) {
        sub["params"]["channels"].push_back("ticker." + i + ".raw");
    }

    std::cout << "Sent subscription message: " << sub.dump() << std::endl;

       
    ws.send(sub.dump());

    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

	ws.stop(); // Stop the WebSocket connection gracefully
}
