#include "db_handler.hpp"
#include <iostream>

void init_db(sqlite3** db) {
    if (sqlite3_open("deribit_data.db", db)) {
        throw std::runtime_error("Can't open database");
    }
    const char* sql = "CREATE TABLE IF NOT EXISTS ticker_data ("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                      "instrument_name TEXT,"
                      "price REAL,"
                      "delta REAL,"
                      "volatility REAL,"
                      "timestamp INTEGER);";

    char* errMsg;
    if (sqlite3_exec(*db, sql, 0, 0, &errMsg) != SQLITE_OK) {
        std::string error = errMsg;
        sqlite3_free(errMsg);
        throw std::runtime_error("SQL error: " + error);
    }
}

void insert_ticker_data(sqlite3* db, const std::string& instrument_name, double price, double delta, double volatility, int64_t timestamp) {
    sqlite3_stmt* stmt;
    const char* sql = "INSERT INTO ticker_data (instrument_name, price, delta, volatility, timestamp) VALUES (?, ?, ?, ?, ?);";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        throw std::runtime_error("Failed to prepare insert");
    }

    sqlite3_bind_text(stmt, 1, instrument_name.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_double(stmt, 2, price);
    sqlite3_bind_double(stmt, 3, delta);
    sqlite3_bind_double(stmt, 4, volatility);
    sqlite3_bind_int64(stmt, 5, timestamp);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        throw std::runtime_error("Failed to execute insert");
    }

    sqlite3_finalize(stmt);
}
