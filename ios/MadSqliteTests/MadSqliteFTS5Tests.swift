//
//  MadSqliteTests.swift
//  MadSqliteTests
//
//  Created by William Kamp on 11/16/16.
//  Copyright © 2016 William Kamp. All rights reserved.
//

import XCTest
import Darwin
@testable import MadSqlite

class MadSqliteFTS5Tests: XCTestCase {

    override func setUp() {
        super.setUp()
    }

    override func tearDown() {
        // Put teardown code here. This method is called after the invocation of each test method in the class.
        super.tearDown()
    }

    func testMatchNear() {
        /*
        https://sqlite.org/fts5.html

        CREATE VIRTUAL TABLE f USING fts5(x);
        INSERT INTO f(rowid, x) VALUES(1, 'A B C D x x x E F x');

        ... MATCH 'NEAR(e d, 4)';                      -- Matches!
        ... MATCH 'NEAR(e d, 3)';                      -- Matches!
        ... MATCH 'NEAR(e d, 2)';                      -- Does not match!

        ... MATCH 'NEAR("c d" "e f", 3)';              -- Matches!
        ... MATCH 'NEAR("c"   "e f", 3)';              -- Does not match!

        ... MATCH 'NEAR(a d e, 6)';                    -- Matches!
        ... MATCH 'NEAR(a d e, 5)';                    -- Does not match!

        ... MATCH 'NEAR("a b c d" "b c" "e f", 4)';    -- Matches!
        ... MATCH 'NEAR("a b c d" "b c" "e f", 3)';    -- Does not match!
         */
        let md = MadSqliteFactory.inMemoryDatabase()!
        md.exec("CREATE VIRTUAL TABLE f USING fts5(x);")
        XCTAssertNil(md.getError());
        md.exec("INSERT INTO f(rowid, x) VALUES(1, 'A B C D x x x E F x');");
        XCTAssertNil(md.getError());

        assertMatches(database: md, query: "SELECT * FROM f WHERE f MATCH 'NEAR(e d, 4)';");
        assertMatches(database: md, query: "SELECT * FROM f WHERE f MATCH 'NEAR(e d, 3)';");
        assertDoesNotMatch(database: md, query: "SELECT * FROM f WHERE f MATCH 'NEAR(e d, 2)';");

        assertMatches(database: md, query: "SELECT * FROM f WHERE f MATCH 'NEAR(\"c d\" \"e f\", 3)';");
        assertDoesNotMatch(database:md, query: "SELECT * FROM f WHERE f MATCH 'NEAR(\"c\" \"e f\", 3)';");

        assertMatches(database: md, query: "SELECT * FROM f WHERE f MATCH 'NEAR(a d e, 6)';");
        assertDoesNotMatch(database: md, query: "SELECT * FROM f WHERE f MATCH 'NEAR(a d e, 5)';");

        assertMatches(database: md, query: "SELECT * FROM f WHERE f MATCH 'NEAR(\"a b c d\" \"b c\" \"e f\", 4)';");
        assertDoesNotMatch(database: md, query: "SELECT * FROM f WHERE f MATCH 'NEAR(\"a b c d\" \"b c\" \"e f\", 3)';");
    }

    func assertMatches(database db: MadDatabase, query sql: String) {
        XCTAssertFalse(queryMatches(database: db, query: sql).isEmpty)
    }

    func assertDoesNotMatch(database db: MadDatabase, query sql: String) {
        XCTAssertTrue(queryMatches(database: db, query: sql).isEmpty)    }

    func queryMatches(database md: MadDatabase, query sql: String) ->[String] {
        let query = md.query(sql)!
        XCTAssertNil(md.getError())
        XCTAssertTrue(query.moveToFirst())
        var rValue = [String]()
        while !(query.isAfterLast()) {
            let value = query.getString(0)
            if !(value?.isEmpty)! {
                rValue.append(value!)
            }
            query.moveToNext()
        }
        return rValue
    }

}
