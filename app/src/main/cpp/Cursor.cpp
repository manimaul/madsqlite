//
// Created by William Kamp on 10/10/16.
//

#include <printf.h>
#include "Cursor.h"

//region Class Methods ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//endregion

//region Constructor ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Cursor::Cursor(sqlite3_stmt *statement) : statement(statement) {
}

Cursor::~Cursor() {
    sqlite3_finalize(statement);
}

//endregion

//region Public Methods ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

bool Cursor::moveToNext() {
    if (!isAfterLast()) {
        stepResult = sqlite3_step(statement);
        return true;
    }
    return false;
}

bool Cursor::isAfterLast() {
    return stepResult != kUninitialized && stepResult != SQLITE_ROW;
}

const std::string Cursor::getString(int columnIndex) const {
    const unsigned char* text = sqlite3_column_text(statement, columnIndex);
    if (text) {
        return std::string(reinterpret_cast<const char*>(text));
    }
    return "";
}

const std::vector<byte> Cursor::getBlob(int columnIndex) const {
    const void *blob = sqlite3_column_blob(statement, columnIndex);
    int sz = sqlite3_column_bytes(statement, columnIndex);
    const byte *charBuf = reinterpret_cast<const byte*>(blob);
    std::vector<byte> value(charBuf, charBuf + sz);
    return value;
}

uint64_t Cursor::getInt(int columnIndex) {
    return (uint64_t) sqlite3_column_int(statement, columnIndex);
}

double Cursor::getReal(int columnIndex) {
    return sqlite3_column_double(statement, columnIndex);
}

int Cursor::getDataCount() {
    return sqlite3_data_count(statement);
}

//endregion

//region Private Methods ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//endregion
