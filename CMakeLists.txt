cmake_minimum_required(VERSION 3.15)
project(BDA_Backend)

set(CMAKE_CXX_STANDARD 17)

find_package(libpqxx REQUIRED)
find_package(Crow REQUIRED)

add_executable(bda_api src/main.cpp)

target_link_libraries(bda_api PRIVATE libpqxx::pqxx Crow::Crow)
