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

//region Members ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

private:

    sqlite3 *db;
    bool isInTransaction = false;
    int execInternal(std::string const &sql);
    const std::unordered_set<std::string> transactionKeyWords = {"BEGIN", "COMMIT", "ROLLBACK"};

//endregion

//region Constructor ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

public:

    /**
     * Opens an in memory database.
     * @return an in memor database.
     */
    Database();

    /**
     * Opens / creates a database.
     * @param dbPath the absolute path of the database to open / create.
     * @return a database.
     */
    Database(std::string const &dbPath);

    virtual ~Database();

//endregion

//region Public Methods ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

public:

    /**
     * Insert values into a table
     *
     * @param table the table to insert into
     * @param values the values to insert
     * @return if the insertion was successful
     */
    bool insert(std::string const &table, ContentValues &values);

    /**
     * Execute a sql query
     *
     * @param sql the query
     * @return a Cursor to retrive query results
     */
    Cursor query(std::string const &sql);

    /**
     * Execute a sql query
     *
     * @param sql the query
     * @param sql query arguments
     * @return a Cursor to retrive query results
     */
    Cursor query(std::string const &sql, std::vector<std::string> const &args);

    /**
     * Execute a sql statement.
     *
     * @param sql a statement to execute
     * @return the number of rows modified by those SQL statements (INSERT, UPDATE or DELETE only)
     */
    int exec(std::string const &sql);

    /**
     * @return the most recent database API call error message.
     */
    std::string getError();

    void beginTransaction();
    void rollbackTransaction();
    void endTransaction();

//endregion

//region Private Methods ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

private:

//endregion

};

#endif //MADSQLITE_DATABASE_H
