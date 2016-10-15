//
// Created by William Kamp on 10/10/16.
//

#include <printf.h>
#include "Cursor.h"

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

int Cursor::getColumnCount() {
    return 0;
}

bool Cursor::moveToNext() {
    return false;
}

bool Cursor::isAfterLast() {
    return false;
}

int Cursor::getPosition() {
    return 0;
}

const sqlstr Cursor::getString(int columnIndex) const {
    return sqlstr();
}

const sqlblob Cursor::getBlob(int columnIndex) const {
    return sqlblob();
}

sqlint Cursor::getInt(int columnIndex) {
    uint64_t i = 0;
    return i;
}

sqlreal Cursor::getReal(int columnIndex) {
    double value = 0;
    return value;
}

Cursor::Cursor(sqlite3_stmt *statement) : statement(statement) {}

Cursor::~Cursor() {
    sqlite3_finalize(statement);
}
