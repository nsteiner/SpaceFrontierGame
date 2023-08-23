#include "database.h"
#include <string>
#include <iostream>

using namespace std;

int Database::createDB(const char* s){
    int exit = 0;
    sqlite3* db;

    exit = sqlite3_open(s, &db);

    sqlite3_close(db);

    return 0;
}

int Database::createTable(const char* s){
    sqlite3* db;

    string sql = "CREATE TABLE IF NOT EXISTS HIGH_SCORES("
            "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
            "HIGH_SCORE     INT NOT NULL);";
    
    try{
        int exit = 0; 
        exit = sqlite3_open(s, &db);

        char* messageError;
        exit = sqlite3_exec(db, sql.c_str(), NULL, 0, &messageError);

        if(exit != SQLITE_OK){
            sqlite3_free(messageError);
        }
        else{
            sqlite3_close(db);
        }
    }
    catch (const exception & e){}

    return 0;
}

void Database::update(const char* s, int newHighScore, bool& highScoreUpdated){
    highScoreUpdated = true;
    
    sqlite3* db;
    int rc = sqlite3_open(s, &db);

    if (rc != SQLITE_OK) {
        std::cerr << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }

    const char* query = "UPDATE HIGH_SCORES SET HIGH_SCORE = ? WHERE ID = 1;";
    sqlite3_stmt* stmt;

    rc = sqlite3_prepare_v2(db, query, -1, &stmt, nullptr);

    if (rc != SQLITE_OK) {
        std::cerr << "Error preparing statement: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }

    rc = sqlite3_bind_int(stmt, 1, newHighScore);

    if (rc != SQLITE_OK) {
        std::cerr << "Error binding parameter: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return;
    }

    rc = sqlite3_step(stmt);

    if (rc != SQLITE_DONE) {
        std::cerr << "Error updating high score: " << sqlite3_errmsg(db) << std::endl;
    } else {
        std::cout << "High score updated successfully!" << std::endl;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
};

int Database::getHighScoreCallback(void* data, int argc, char** argv, char** azColName) {
    int* highScore = static_cast<int*>(data);
    if (argc > 0) {
        *highScore = std::stoi(argv[0]);
    }
    return 0;
}

int::Database:: getHighScore(const char* s){
    sqlite3* db;
    int highScore = 0;
    int rc = sqlite3_open(s, &db);

    if (rc != SQLITE_OK) {
        std::cerr << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return highScore;
    }

    char query[] = "SELECT HIGH_SCORE FROM HIGH_SCORES WHERE ID = 1;";
    rc = sqlite3_exec(db, query, getHighScoreCallback, &highScore, nullptr);

    if (rc != SQLITE_OK) {
        std::cerr << "Error executing SELECT query: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_close(db);
    return highScore;
};