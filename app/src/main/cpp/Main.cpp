

#include <string>
#include <iostream>
#include "Database.h"
#include "ContentValues.h"

int main() {
    auto cv = ContentValues();
    cv.putString("x", "1970");
    std::cout << "key getAsInteger() " << cv.getAsInteger("key") << std::endl;

    auto db = Database("/Users/williamkamp/Desktop/test.s3db");
    auto msg = db.execute("CREATE TABLE test(x INTEGER);");
    std::cout << "Message: " << msg << std::endl;

    db.insert("test", cv);

//    auto c = db.query("", "");
//    Cursor *cursor = c.release();
//    delete(cursor);
}
