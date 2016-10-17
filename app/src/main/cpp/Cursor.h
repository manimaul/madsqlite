//
// Created by William Kamp on 10/10/16.
//

#ifndef PROJECT_CURSOR_H
#define PROJECT_CURSOR_H

#include "Constants.h"
#include "sqlite-amalgamation-3140200/sqlite3.h"

class Cursor {

//region Members ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

private:
    static const int kUninitialized = -1;
    sqlite3_stmt *statement;
    int stepResult = kUninitialized;

//endregion

//region Constructor ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

public:

    Cursor(sqlite3_stmt *statement);
    virtual ~Cursor();

//endregion

//region Public Methods ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

public:

    bool moveToNext();
    bool isAfterLast();
    int getDataCount();
    const sqlstr getString(int columnIndex) const;
    const sqlblob getBlob(int columnIndex) const;
    sqlint getInt(int columnIndex);
    sqlreal getReal(int columnIndex);

//endregion

//region Private Methods ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

private:

//endregion

};


#endif //PROJECT_CURSOR_H
