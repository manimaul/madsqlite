

#include <string>
#include <iostream>
#include "Database.h"

static void print(std::string const &msg, sqlreal &value) {
    std::cout << msg << " " << value << std::endl;
}

static void print(std::string const &msg, sqlstr &value) {
    std::cout << msg << " " << value << std::endl;
}

static void print(std::string const &msg, int &value) {
    std::cout << msg << " " << value << std::endl;
}

static void print(std::string const &msg, sqlint &value) {
    std::cout << msg << " " << value << std::endl;
}

static void print(std::string const &msg, sqlblob &blob) {
    std::cout << msg << " ";
    for (byte &b : blob) {
        std::cout << b;
    }
    std::cout << std::endl;
}

int main() {
    // Create an in-memory database
    auto db = Database();
    db.exec("CREATE TABLE test(x INTEGER, "
                    "y TEXT, "
                    "z BLOB);");

    // Insert in database
    auto cv = ContentValues();
    char *blob = "i'm a blob";
    cv.putBlob("z", blob, strlen(blob));
    cv.putInteger("y", 7070);
    cv.putInteger("x", 1970);
    db.insert("test", cv);

    cv.clear();
    db.insert("test", cv);

    cv.clear();
    cv.putInteger("y", 61);
    db.insert("test", cv);

    auto cursor = db.query("SELECT * FROM test");
    cursor.moveToNext();
    while (!cursor.isAfterLast()) {
        sqlint storedX = cursor.getInt(0);
        print("x:", storedX);
        sqlstr storedY = cursor.getString(1);
        print("y:", storedY);
        sqlblob storedBlob = cursor.getBlob(2);
        print("z:", storedBlob);
        cursor.moveToNext();
    }
}
