//
// Created by William Kamp on 10/9/16.
//

#include <iostream>
#include "Database.h"

static int callback(void *data, int argc, char **argv, char **azColName) {
    //todo:
    Cursor *cursor = reinterpret_cast<Cursor *>(data);
    int i;
    for (i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

std::string Database::execute(std::string sql) {
    char *errorMessage = 0;
    int rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errorMessage);
    std::string message;
    if (rc == SQLITE_OK) {
        message = "OK";
    } else {
        message = std::string(errorMessage);
        sqlite3_free(errorMessage);
    }
    return message;
}

std::unique_ptr<Cursor> Database::query(std::string sql, std::vector<std::string> args) {
    auto cursor = std::unique_ptr<Cursor>();
    //todo:
//    char *errorMessage = 0;
//    sqlite3_exec(db, sql.c_str(), &callback, cursor.get(), &errorMessage);
    return cursor;
}

long Database::insert(std::string table, ContentValues values) {
    if (values.isEmpty()) {
        return -1;
    }
    // INSERT INTO [table] ([row1], [row2]) VALUES (0,"value");
    // INSERT INTO [table] ([?], [?]) VALUES (?,?);
    std::string sql = "INSERT INTO [" + table + "] (";
    std::string bindings = " VALUES (";
    auto keys = values.keys();
    for (auto key: keys) {
        sql += "[" + key + "]";

        if (key == keys.back()) {
            sql += ")";
            bindings += "?);";
        } else {
            sql += ",";
            bindings += "?,";
        }
    }
    sql = sql + bindings;
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0) != SQLITE_OK) {
        std::cout << "Could not prepare statement." << std::endl;
        return -1;
    }

    for (int i = 0; i < keys.size(); ++i) {
        std::string key = keys.at((unsigned long) i);
        switch (values.typeForKey(key)) {
            case ContentValues::NONE: {
                break;
            }
            case ContentValues::INT: {
                if (sqlite3_bind_int64(stmt, i + 1, values.getAsInteger(key)) != SQLITE_OK) {
                    std::cout << "Could not bind statement." << std::endl;
                    return -1;
                };
                break;
            }
            case ContentValues::REAL: {
                if (sqlite3_bind_double(stmt, i + 1, values.getAsReal(key)) != SQLITE_OK) {
                    std::cout << "Could not bind statement." << std::endl;
                    return -1;
                };
                break;
            }
            case ContentValues::TEXT: {
                const std::string &text = values.getAsText(key);
                if (sqlite3_bind_text(stmt, i + 1, text.c_str(), -1, SQLITE_STATIC) != SQLITE_OK) {
                    std::cout << "Could not bind statement." << std::endl;
                    return -1;
                };
                break;
            }
            case ContentValues::BLOB: {
                const std::vector<byte> vector = values.getAsBlob(key);
                if (sqlite3_bind_blob(stmt, i + 1, vector.begin(), (int) vector.size(), SQLITE_STATIC) != SQLITE_OK) {
                    std::cout << "Could not bind statement." << std::endl;
                    return -1;
                };
                break;
            }
        }
    }

    //sqlite3_reset(stmt);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cout << "Could not step (execute) stmt." << std::endl;
        return -1;
    }

    return 0;
}
