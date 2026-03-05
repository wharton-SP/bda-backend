#include "crow.h"
#include <pqxx/pqxx>
#include <iostream>

void check_db_connection () {
    try {
        pqxx::connection c("host=localhost port=5432 dbname=gestion_etudiant user=bda password=bdabda");
        std::cout << "Successfully Connected !" << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Error connecting to database: " << e.what() << std::endl;
    }
}

int main () {
    crow::SimpleApp app;

    CROW_ROUTE(app, "/health")([](){
        return "API is healthy!";
    });

    check_db_connection();

    app.port(1890).multithreaded().run();
    return 0;
}
