#include "crow.h"
#include <pqxx/pqxx>
#include <iostream>


void check_db_connection () {
    try {
        pqxx::connection c("host=localhost port=5432 dbname=gestion_etudiant user=bda password=bdabda");
        std::cout << "============= Successfully Connected ! =============" << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Error connecting to database: " << e.what() << std::endl;
    }
}

int main () {
    int port = 1890;
    crow::SimpleApp app;
    app.loglevel(crow::LogLevel::Warning);

    CROW_ROUTE(app, "/health")([](){
        return "API is healthy!";
    });

    check_db_connection();
    std::cout << "============= Starting API on : 0.0.0.0:" << port << " =============" << std::endl;


    app.port(port).multithreaded().run();
    return 0;
}
