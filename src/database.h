#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>

class Database{
    public:
        static int createDB(const char* s);
        static int createTable(const char* s);
        static void update(const char* s, int newHighScore, bool& highScoreUpdated);
        static int getHighScoreCallback(void* data, int argc, char** argv, char** azColName);
        static int getHighScore(const char* s);
};



#endif
