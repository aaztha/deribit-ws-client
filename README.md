# Deribit WebSocket Client

This project implements a C++ client to:

#Authenticate with Deribit REST API  
#Fetch active BTC/ETH option instruments  
#Subscribe to Deribit WebSocket for live ticker updates  
#Parse JSON messages using `nlohmann/json`  
#Save `instrument_name`, `price`, `delta`, `volatility`, `timestamp` to SQLite database

## Build Instructions:

### Dependencies:
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
```
#If using vcpkg and facing error in getting installed packages such as sqlite, then run `cmake .. -DCMAKE_TOOLCHAIN_FILE=C:/path_to_vcpkg/scripts/buildsystems/vcpkg.cmake` instead of `cmake ..`



### To Run:
1. Go inside build folder 
2. Run this command: `.\Debug\deribit_ws_client.exe`
