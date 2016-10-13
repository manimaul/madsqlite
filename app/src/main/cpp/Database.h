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

    Database(std::string const &dbPath);

    virtual ~Database();

    //endregion

    long insert(std::string const &table, ContentValues &values);

    std::unique_ptr<Cursor> query(std::string const  &sql, std::vector<std::string> &args);

    std::string execute(std::string const &sql);
};


#endif //MADSQLITE_DATABASE_H
