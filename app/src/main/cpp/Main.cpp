

#include <string>
#include <iostream>
#include "Database.h"

int main() {
    // Create an in-memory database
    auto db = Database();
    db.exec("CREATE TABLE test(x INTEGER, "
                                  "y TEXT, "
                                  "z BLOB);");

    // Insert in database
    auto cv = ContentValues();
    char* blob = "i'm a blob";
    cv.putBlob("z", blob, strlen(blob));
    cv.putString("x", "1970");
    db.insert("test", cv);

    auto cursor = db.query("SELECT * FROM test WHERE ", {""});
}
