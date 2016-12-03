//
//  MadSqliteSwiftTests.swift
//  MadSqliteSwiftTests
//
//  Created by William Kamp on 12/2/16.
//  Copyright © 2016 William Kamp. All rights reserved.
//

import XCTest
@testable import MadSqliteSwift

class MadSqliteSwiftTests: XCTestCase {
    
    override func setUp() {
        super.setUp()
        // Put setup code here. This method is called before the invocation of each test method in the class.
    }
    
    override func tearDown() {
        // Put teardown code here. This method is called after the invocation of each test method in the class.
        super.tearDown()
    }
    
    func testInsertInt() {
        let md = MadDatabase()
        _ = md.exec(sql: "CREATE TABLE test(keyInt INTEGER);")
        XCTAssertNil(md.getError())
        
        let cv = MadContentValues()
        cv.putInt(key: "keyInt", value: Int.max)
        _ = md.insert(table: "test", values: cv)
        XCTAssertNil(md.getError())
        
        cv.clear()
        cv.putInt(key: "keyInt", value: Int.min)
        _ = md.insert(table: "test", values: cv)
        XCTAssertNil(md.getError())
        
        let query = md.query(sql: "SELECT keyInt FROM test;")
        XCTAssertNotNil(query)
        XCTAssertTrue(query.moveToFirst())
        XCTAssertFalse(query.isAfterLast())
        let firstResult = query.getInt(column: 0)
        XCTAssertTrue(Int.max == firstResult)
        
        XCTAssertTrue(query.moveToNext())
        XCTAssertFalse(query.isAfterLast())
        let secondResult = query.getInt(column: 0)
        XCTAssertTrue(Int.min == secondResult)
        
        XCTAssertTrue(query.moveToNext())
        XCTAssertTrue(query.isAfterLast())
    }
    
    func testInsertInt64() {
        let md = MadDatabase()
        _ = md.exec(sql: "CREATE TABLE test(keyInt INTEGER);")
        XCTAssertNil(md.getError())
        
        let cv = MadContentValues()
        cv.putInt64(key: "keyInt", value: Int64.max)
        _ = md.insert(table: "test", values: cv)
        XCTAssertNil(md.getError())
        
        cv.clear()
        cv.putInt64(key: "keyInt", value: Int64.min)
        _ = md.insert(table: "test", values: cv)
        XCTAssertNil(md.getError())
        
        let query = md.query(sql: "SELECT keyInt FROM test;")
        XCTAssertNotNil(query)
        XCTAssertTrue(query.moveToFirst())
        XCTAssertFalse(query.isAfterLast())
        let firstResult = query.getInt64(column: 0)
        XCTAssertEqual(Int64.max, firstResult);
        
        XCTAssertTrue(query.moveToNext())
        XCTAssertFalse(query.isAfterLast())
        let secondResult = query.getInt64(column: 0)
        XCTAssertEqual(Int64.min, secondResult);
        
        XCTAssertTrue(query.moveToNext())
        XCTAssertTrue(query.isAfterLast())
        
    }
    
    func testInsertReal() {
        let md = MadDatabase()
        _ = md.exec(sql: "CREATE TABLE test(keyReal REAL);")
        XCTAssertNil(md.getError())
        
        let cv = MadContentValues()
        cv.putReal(key: "keyReal", value: DBL_MAX)
        _ = md.insert(table: "test", values: cv)
        XCTAssertNil(md.getError())
        
        cv.clear()
        cv.putReal(key: "keyReal", value: DBL_MIN)
        _ = md.insert(table: "test", values: cv)
        XCTAssertNil(md.getError())
        
        let query = md.query(sql: "SELECT keyReal FROM test;")
        XCTAssertNotNil(query)
        XCTAssertTrue(query.moveToFirst())
        XCTAssertFalse(query.isAfterLast())
        let firstResult = query.getReal(column: 0)
        
        XCTAssertTrue(query.moveToNext())
        XCTAssertFalse(query.isAfterLast())
        let secondResult = query.getReal(column: 0)
        
        XCTAssertTrue(query.moveToNext())
        XCTAssertTrue(query.isAfterLast())
        XCTAssertFalse(query.moveToNext())
        
        XCTAssertTrue(DBL_MAX == firstResult)
        XCTAssertTrue(DBL_MIN == secondResult)
    }
    
    func testInsertBlob() {
        let md = MadDatabase()
        _ = md.exec(sql: "CREATE TABLE test(keyBlob BLOB);")
        XCTAssertNil(md.getError())
        
        let cv = MadContentValues()
        let data = "data".data(using: .utf8)
        cv.putBlob(key: "keyBlob", value: data)
        XCTAssertNil(md.getError())
        
        _ = md.insert(table: "test", values: cv)
        XCTAssertNil(md.getError())
        
        let query = md.query(sql: "SELECT keyBlob FROM test;")
        XCTAssertNotNil(query)
        XCTAssertTrue(query.moveToFirst())
        XCTAssertFalse(query.isAfterLast())
        let blobResult = query.getBlob(column: 0)
        let strResult = query.getString(column: 0)
        
        XCTAssertTrue(query.moveToNext())
        XCTAssertTrue(query.isAfterLast())
        XCTAssertFalse(query.moveToNext())
        
        XCTAssertEqual("data", String(data: blobResult, encoding: .utf8))
        XCTAssertEqual("data", strResult)
    }
    
    func testInsertText() {
        let md = MadDatabase()
        _ = md.exec(sql: "CREATE TABLE test(keyText TEXT);")
        XCTAssertNil(md.getError())
        
        let cv = MadContentValues()
        let text = "the quick brown fox jumped over the lazy dog!"
        cv.putString(key: "keyText", value: text)
        XCTAssertNil(md.getError())
        
        XCTAssertTrue(md.insert(table: "test", values: cv))
        XCTAssertNil(md.getError())
        
        let query = md.query(sql: "SELECT keyText FROM test;")
        XCTAssertNotNil(query)
        XCTAssertTrue(query.moveToFirst())
        XCTAssertFalse(query.isAfterLast())
        let strResult = query.getString(column: 0)
        
        XCTAssertTrue(query.moveToNext())
        XCTAssertTrue(query.isAfterLast())
        XCTAssertFalse(query.moveToNext())
        
        XCTAssertEqual(text, strResult)
    }
    
    func testQueryArgs() {
        let md = MadDatabase()
        _ = md.exec(sql: "CREATE TABLE test(keyInt INTEGER, keyText TEXT);")
        XCTAssertNil(md.getError())
        
        let cv = MadContentValues()
        cv.putString(key: "keyText", value: "the quick brown fox")
        cv.putString(key: "keyInt", value: "99")
        XCTAssertTrue(md.insert(table: "test", values: cv))
        XCTAssertNil(md.getError())
        
        cv.clear()
        cv.putString(key: "keyText", value: "the slow white tortoise")
        cv.putInt(key: "keyInt", value: 34)
        XCTAssertTrue(md.insert(table: "test", values: cv));
        XCTAssertNil(md.getError())
        
        let query = md.query(sql: "SELECT keyText,keyInt FROM test WHERE keyInt is ?;", args: ["99"])
        XCTAssertNil(md.getError())
        XCTAssertTrue(query.moveToFirst())
        XCTAssertFalse(query.isAfterLast())
        let value = query.getString(column: 0)
        let number = query.getReal(column: 1)
        XCTAssertTrue(query.moveToNext())
        XCTAssertTrue(query.isAfterLast())
        
        XCTAssertEqual(99, number);
        XCTAssertEqual("the quick brown fox", value);
        
        let query2 = md.query(sql: "SELECT keyText,keyInt FROM test WHERE keyInt is ?;", args: ["34"])
        XCTAssertNil(md.getError())
        XCTAssertTrue(query2.moveToFirst())
        XCTAssertFalse(query2.isAfterLast())
        let value2 = query2.getString(column: 0)
        let number2 = query2.getReal(column: 1)
        XCTAssertTrue(query2.moveToNext())
        XCTAssertTrue(query2.isAfterLast())
        
        XCTAssertEqual(34, number2);
        XCTAssertEqual("the slow white tortoise", value2);
        
    }
    
    func testMultiIndexQuery() {
        let md = MadDatabase()
        _ = md.exec(sql: "CREATE TABLE test(keyInt INTEGER, keyReal REAL, keyText TEXT);")
        multiIndexQuery(database: md)
        XCTAssertNil(md.getError())
    }
    
    func testFileSystemDatabase() {
        // ~/Library/Developer/CoreSimulator/Devices/ED77F264-2FF3-4DBF-A2F6-F8CBC2D6EE15/data/Library/test.s3db
        let md = MadDatabase(name: "test.s3db")
        _ = md.exec(sql: "DROP TABLE IF EXISTS test")
        XCTAssertNil(md.getError())
        _ = md.exec(sql: "CREATE TABLE test(keyInt INTEGER, keyReal REAL, keyText TEXT);")
        XCTAssertNil(md.getError())
        
        multiIndexQuery(database: md)
    }
    
    func multiIndexQuery(database md: MadDatabase) {
        let cv = MadContentValues()
        cv.putString(key: "keyText", value: "the quick brown fox")
        cv.putInt(key: "keyInt", value: 99)
        cv.putReal(key: "keyReal", value: 23829.3)
        XCTAssertTrue(md.insert(table: "test", values: cv))
        XCTAssertNil(md.getError())
        
        cv.clear()
        cv.putString(key: "keyText", value: "the slow red tortoise")
        cv.putInt(key:"keyInt", value: 42)
        cv.putReal(key: "keyReal", value: 3829.3)
        XCTAssertTrue(md.insert(table: "test", values: cv))
        XCTAssertNil(md.getError())
        
        let query = md.query(sql: "SELECT * FROM test;")
        XCTAssertNil(md.getError())
        
        XCTAssertTrue(query.moveToFirst())
        XCTAssertEqual(23829.3, query.getReal(column: 1))
        XCTAssertEqual("the quick brown fox", query.getString(column: 2))
        XCTAssertEqual(99, query.getInt(column: 0))
        XCTAssertFalse(query.isAfterLast())
        
        XCTAssertTrue(query.moveToNext())
        XCTAssertFalse(query.isAfterLast())
        XCTAssertEqual(3829.3, query.getReal(column: 1))
        XCTAssertEqual("the slow red tortoise", query.getString(column: 2))
        XCTAssertEqual(42, query.getInt(column: 0))
        XCTAssertFalse(query.isAfterLast())
        
        XCTAssertTrue(query.moveToNext())
        XCTAssertFalse(query.moveToNext())
        XCTAssertTrue(query.isAfterLast())
    }
    
}
