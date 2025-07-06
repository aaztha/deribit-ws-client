cmake_minimum_required(VERSION 3.14)
project(deribit_ws_client)

set(CMAKE_CXX_STANDARD 17)

find_package(cpr CONFIG REQUIRED)
find_package(SQLite3 REQUIRED)
find_package(ixwebsocket CONFIG REQUIRED)

add_executable(deribit_ws_client
  main.cpp
  rest_api.cpp
  ws_client.cpp
  db_handler.cpp
)

target_link_libraries(deribit_ws_client PRIVATE cpr::cpr SQLite::SQLite3 ixwebsocket::ixwebsocket)

if (WIN32)
    target_link_libraries(deribit_ws_client PRIVATE bcrypt)
endif()


# No need for target_include_directories for json since vcpkg handles it
