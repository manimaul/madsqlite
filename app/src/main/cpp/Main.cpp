

#include <string>
#include <iostream>
#include "Database.h"

int main() {
    // Create / open database
    auto db = Database("/Users/williamkamp/Desktop/test.s3db");
    auto msg = db.execute("CREATE TABLE test(x INTEGER);");
    std::cout << "Message: " << msg << std::endl;

    // Insert in database
    auto cv = ContentValues();
    cv.putString("x", "1970");
    db.insert("test", cv);
}
