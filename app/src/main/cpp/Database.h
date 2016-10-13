//
// Created by William Kamp on 10/9/16.
//

#ifndef MADSQLITE_DATABASE_H
#define MADSQLITE_DATABASE_H


#include "sqlite-amalgamation-3140200/sqlite3.h"
#include "Cursor.h"
#include "Constants.h"
#include "ContentValues.h"
#include <string>
#include <unordered_map>

class Database {

private:
    sqlite3 *db;

public:

    //region CTOR

    Database(std::string dbPath) {
        sqlite3_open(dbPath.c_str(), &db);
    }

    virtual ~Database() {
        sqlite3_close(db);
    }

    //endregion

    long insert(std::string table, ContentValues values);

    std::unique_ptr<Cursor> query(std::string sql, std::vector<std::string> args);

    std::string execute(std::string sql);
};


#endif //MADSQLITE_DATABASE_H
