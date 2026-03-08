cmake_minimum_required(VERSION 3.15)
project(BDA_Backend)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

find_package(libpqxx REQUIRED)
find_package(Crow REQUIRED)

file(GLOB_RECURSE SOURCES 
    "src/main.cpp"
    "src/models/*.cpp"
    "src/controllers/*.cpp"
    "src/routes/*.cpp"
)

add_executable(bda_api ${SOURCES})

target_link_libraries(bda_api PRIVATE 
    libpqxx::pqxx 
    Crow::Crow
    asio::asio
    pthread
)