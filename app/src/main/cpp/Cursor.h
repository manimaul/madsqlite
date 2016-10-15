//
// Created by William Kamp on 10/10/16.
//

#ifndef PROJECT_CURSOR_H
#define PROJECT_CURSOR_H


#include "Constants.h"
#include "sqlite-amalgamation-3140200/sqlite3.h"

class Cursor {

private:
    sqlite3_stmt *statement;
public:
    Cursor(sqlite3_stmt *statement);
    virtual ~Cursor();

public:

    int getColumnCount();
    bool moveToNext();
    bool isAfterLast();
    int getPosition();

    const sqlstr getString(int columnIndex) const;
    const sqlblob getBlob(int columnIndex) const;
    sqlint getInt(int columnIndex);
    sqlreal getReal(int columnIndex);

};


#endif //PROJECT_CURSOR_H
