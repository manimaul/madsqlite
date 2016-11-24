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
        XCTAssertEqual(Int64.max, firstResult?.int64Value);
        
        XCTAssertTrue(query.moveToNext())
        XCTAssertFalse(query.isAfterLast())
        let secondResult = query.getInt(0)
        XCTAssertEqual(Int64.min, secondResult?.int64Value);
        
        XCTAssertTrue(query.moveToNext())
        XCTAssertTrue(query.isAfterLast())
        
    }
    
    func testInsertReal() {
        let md = MadDatabase()!
        md.exec("CREATE TABLE test(keyReal REAL);")
        XCTAssertNil(md.getError())
        
        let cv = MadContentValuesFactory.values()!
        cv.putReal("keyReal", withValue: NSNumber(value: DBL_MAX))
        md.insert("test", with: cv)
        XCTAssertNil(md.getError())
        
        cv.clear()
        cv.putReal("keyReal", withValue: NSNumber(value: DBL_MIN))
        md.insert("test", with: cv)
        XCTAssertNil(md.getError())
        
        let query = md.query("SELECT keyReal FROM test;")!
        XCTAssertNotNil(query)
        XCTAssertTrue(query.moveToFirst())
        XCTAssertFalse(query.isAfterLast())
        let firstResult = query.getReal(0)
        
        XCTAssertTrue(query.moveToNext())
        XCTAssertFalse(query.isAfterLast())
        let secondResult = query.getReal(0)
        
        
        XCTAssertTrue(query.moveToNext())
        XCTAssertTrue(query.isAfterLast())
        XCTAssertFalse(query.moveToNext())

        XCTAssertTrue(DBL_MAX == firstResult?.doubleValue)
        XCTAssertTrue(DBL_MIN == secondResult?.doubleValue)
    }

}
