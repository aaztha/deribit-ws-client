#pragma once

#include <sqlite3.h>
#include <string>

void init_db(sqlite3** db);
void insert_ticker_data(sqlite3* db, const std::string& instrument_name, double price, double delta, double volatility, int64_t timestamp);
