# Deribit WebSocket Client

This project implements a C++ client to:

#Authenticate with Deribit REST API  
#Fetch active BTC/ETH option instruments  
#Subscribe to Deribit WebSocket for live ticker updates  
#Parse JSON messages using `nlohmann/json`  
#Save `instrument_name`, `price`, `delta`, `volatility`, `timestamp` to SQLite database

======================================================================================================================
## Build Instructions:

### Dependencies:
-  C++17
- CMake
- `nlohmann/json`
- `ixwebsocket`
- `cpr`
- `sqlite3`

### Build
```bash
mkdir build
cd build
cmake ..
cmake --build .
