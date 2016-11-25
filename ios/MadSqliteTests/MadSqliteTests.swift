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
        let md = MadSqliteFactory.inMemoryDatabase()!
        md.exec("CREATE TABLE test(keyInt INTEGER);")
        XCTAssertNil(md.getError())

        let cv = MadSqliteFactory.contentValues()!
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
        let md = MadSqliteFactory.inMemoryDatabase()!
        md.exec("CREATE TABLE test(keyInt INTEGER);")
        XCTAssertNil(md.getError())

        let cv = MadSqliteFactory.contentValues()!
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
        let md = MadSqliteFactory.inMemoryDatabase()!
        md.exec("CREATE TABLE test(keyReal REAL);")
        XCTAssertNil(md.getError())

        let cv = MadSqliteFactory.contentValues()!
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

    func testInsertBlob() {
        let md = MadSqliteFactory.inMemoryDatabase()!
        md.exec("CREATE TABLE test(keyBlob BLOB);")
        XCTAssertNil(md.getError())

        let cv = MadSqliteFactory.contentValues()!
        let data = "data".data(using: .utf8)
        cv.putBlob("keyBlob", withValue: data)
        XCTAssertNil(md.getError())

        md.insert("test", with: cv)
        XCTAssertNil(md.getError())

        let query = md.query("SELECT keyBlob FROM test;")!
        XCTAssertNotNil(query)
        XCTAssertTrue(query.moveToFirst())
        XCTAssertFalse(query.isAfterLast())
        let blobResult = query.getBlob(0)
        let strResult = query.getString(0)

        XCTAssertTrue(query.moveToNext())
        XCTAssertTrue(query.isAfterLast())
        XCTAssertFalse(query.moveToNext())

        XCTAssertEqual("data", String(data: blobResult!, encoding: .utf8))
        XCTAssertEqual("data", strResult)
    }

    func testInsertText() {
        let md = MadSqliteFactory.inMemoryDatabase()!
        md.exec("CREATE TABLE test(keyText TEXT);")
        XCTAssertNil(md.getError())

        let cv = MadSqliteFactory.contentValues()!
        let text = "the quick brown fox jumped over the lazy dog!"
        cv.put("keyText", withValue: text)
        XCTAssertNil(md.getError())

        XCTAssertTrue(md.insert("test", with: cv))
        XCTAssertNil(md.getError())

        let query = md.query("SELECT keyText FROM test;")!
        XCTAssertNotNil(query)
        XCTAssertTrue(query.moveToFirst())
        XCTAssertFalse(query.isAfterLast())
        let strResult = query.getString(0)

        XCTAssertTrue(query.moveToNext())
        XCTAssertTrue(query.isAfterLast())
        XCTAssertFalse(query.moveToNext())

        XCTAssertEqual(text, strResult)
    }

    func testQueryArgs() {
        let md = MadSqliteFactory.inMemoryDatabase()!
        md.exec("CREATE TABLE test(keyInt INTEGER, keyText TEXT);")
        XCTAssertNil(md.getError())

        let cv = MadSqliteFactory.contentValues()!
        cv.put("keyText", withValue: "the quick brown fox")
        cv.putInteger("keyInt", withValue: 99)
        XCTAssertTrue(md.insert("test", with: cv))
        XCTAssertNil(md.getError())

        cv.clear()
        cv.put("keyText", withValue: "the slow white tortoise")
        cv.putInteger("keyInt", withValue: 34)
        XCTAssertTrue(md.insert("test", with: cv));
        XCTAssertNil(md.getError())

        let query = md.query("SELECT keyText,keyInt FROM test WHERE keyInt is ?;", withArgs: ["99"])!
        XCTAssertNil(md.getError())
        XCTAssertTrue(query.moveToFirst())
        XCTAssertFalse(query.isAfterLast())
        let value = query.getString(0)
        let number = query.getReal(1)
        XCTAssertTrue(query.moveToNext())
        XCTAssertTrue(query.isAfterLast())

        XCTAssertEqual(99, number);
        XCTAssertEqual("the quick brown fox", value);

        let query2 = md.query("SELECT keyText,keyInt FROM test WHERE keyInt is ?;", withArgs: ["34"])!
        XCTAssertNil(md.getError())
        XCTAssertTrue(query2.moveToFirst())
        XCTAssertFalse(query2.isAfterLast())
        let value2 = query2.getString(0)
        let number2 = query2.getReal(1)
        XCTAssertTrue(query2.moveToNext())
        XCTAssertTrue(query2.isAfterLast())

        XCTAssertEqual(34, number2);
        XCTAssertEqual("the slow white tortoise", value2);

    }

    func testMultiIndexQuery() {
        let md = MadSqliteFactory.inMemoryDatabase()!
        md.exec("CREATE TABLE test(keyInt INTEGER, keyReal REAL, keyText TEXT);")
        XCTAssertNil(md.getError())

        let cv = MadSqliteFactory.contentValues()!
        cv.put("keyText", withValue: "the quick brown fox")
        cv.putInteger("keyInt", withValue: 99)
        cv.putReal("keyReal", withValue: 23829.3)
        XCTAssertTrue(md.insert("test", with: cv))
        XCTAssertNil(md.getError())

        cv.clear()
        cv.put("keyText", withValue: "the slow red tortoise")
        cv.putInteger("keyInt", withValue: 42)
        cv.putReal("keyReal", withValue: 3829.3)
        XCTAssertTrue(md.insert("test", with: cv))
        XCTAssertNil(md.getError())

        let query = md.query("SELECT * FROM test;")!
        XCTAssertNil(md.getError())

        XCTAssertTrue(query.moveToFirst())
        XCTAssertEqual(23829.3, query.getReal(1))
        XCTAssertEqual("the quick brown fox", query.getString(2))
        XCTAssertEqual(99, query.getInt(0))
        XCTAssertFalse(query.isAfterLast())

        XCTAssertTrue(query.moveToNext())
        XCTAssertFalse(query.isAfterLast())
        XCTAssertEqual(3829.3, query.getReal(1))
        XCTAssertEqual("the slow red tortoise", query.getString(2))
        XCTAssertEqual(42, query.getInt(0))
        XCTAssertFalse(query.isAfterLast())

        XCTAssertTrue(query.moveToNext())
        XCTAssertFalse(query.moveToNext())
        XCTAssertTrue(query.isAfterLast())
    }

}
