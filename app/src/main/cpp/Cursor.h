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
    sqlite3_stmt *statement;
    int count = 0;
    int position = 0;

//endregion

//region Constructor ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

public:

    Cursor(sqlite3_stmt *statement);
    Cursor(Cursor &&curs);
    Cursor(Cursor &curs) = delete; // disallow copy
    virtual ~Cursor();

//endregion

//region Public Methods ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

public:

    bool moveToFirst();
    bool moveToPosition(int p);
    int getCount();
    bool moveToNext();
    bool isAfterLast();
    const std::string getString(int columnIndex) const;
    const std::vector<byte> getBlob(int columnIndex) const;
    uint64_t getInt(int columnIndex);
    double getReal(int columnIndex);

//endregion

//region Private Methods ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

private:
    int evaluateCount();

//endregion

};


#endif //PROJECT_CURSOR_H
