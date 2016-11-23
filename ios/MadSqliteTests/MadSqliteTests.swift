//
//  MadSqliteTests.swift
//  MadSqliteTests
//
//  Created by William Kamp on 11/16/16.
//  Copyright © 2016 William Kamp. All rights reserved.
//

import XCTest
@testable import MadSqlite

class MadSqliteTests: XCTestCase {

    override func setUp() {
        super.setUp()
    }

    override func tearDown() {
        // Put teardown code here. This method is called after the invocation of each test method in the class.
        super.tearDown()
    }

    func testInsertInt() {
        let md = MadDatabase()!
        md.exec("CREATE TABLE test(keyInt INTEGER);")
        XCTAssertNil(md.getError())

        let cv = MadContentValuesFactory.values()!
        cv.putInteger("keyInt", withValue: NSNumber(value: Int.max))
        md.insert("test", with: cv)
        XCTAssertNil(md.getError())

        cv.clear()
        cv.putInteger("keyInt", withValue: NSNumber(value: Int.min))
        md.insert("test", with: cv)
        XCTAssertNil(md.getError())

        let query = md.query("SELECT keyInt FROM test;")!
        XCTAssertNotNil(query)
        XCTAssertTrue(query.moveToFirst())
        XCTAssertFalse(query.isAfterLast())
        let firstResult = query.getInt(0)
        XCTAssertTrue(Int.max == firstResult?.intValue)

        XCTAssertTrue(query.moveToNext())
        XCTAssertFalse(query.isAfterLast())
        let secondResult = query.getInt(0)
        XCTAssertTrue(Int.min == secondResult?.intValue)

        XCTAssertTrue(query.moveToNext())
        XCTAssertTrue(query.isAfterLast())
    }

    func testInsertInt64() {
        let md = MadDatabase()!
        md.exec("CREATE TABLE test(keyInt INTEGER);")
        XCTAssertNil(md.getError())

        let cv = MadContentValuesFactory.values()!
        cv.putInteger("keyInt", withValue: NSNumber(value: Int64.max))
        md.insert("test", with: cv)
        XCTAssertNil(md.getError())

        cv.clear()
        cv.putInteger("keyInt", withValue: NSNumber(value: Int64.min))
        md.insert("test", with: cv)
        XCTAssertNil(md.getError())

        let query = md.query("SELECT keyInt FROM test;")!
        XCTAssertNotNil(query)
        XCTAssertTrue(query.moveToFirst())
        XCTAssertFalse(query.isAfterLast())
        let firstResult = query.getInt(0)
        XCTAssertTrue(Int64.max == firstResult?.int64Value)

        XCTAssertTrue(query.moveToNext())
        XCTAssertFalse(query.isAfterLast())
        let secondResult = query.getInt(0)
        XCTAssertTrue(Int64.min == secondResult?.int64Value)

        XCTAssertTrue(query.moveToNext())
        XCTAssertTrue(query.isAfterLast())
    }

}
