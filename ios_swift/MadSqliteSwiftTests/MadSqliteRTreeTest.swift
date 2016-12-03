//
//  MadSqliteRTreeTest.swift
//  MadSqlite
//
//  Created by William Kamp on 11/27/16.
//  Copyright © 2016 William Kamp. All rights reserved.
//

import Foundation
import XCTest
@testable import MadSqliteSwift

class MadSqliteRTreeTest: XCTestCase {
    
    func testRTreeBetween() {
        let PRECISION_MAX_DELTA = 0.00002
        
        let md = givenAnRTreeDatabase()
        givenValuesInserted(database: md)
        givenContentValuesInserted(database: md)
        
        var query = md.query(sql: "SELECT * FROM demo_index WHERE id=2;")
        XCTAssertTrue(query.moveToFirst())
        XCTAssertEqual(2, query.getInt(column: 0))
        XCTAssertEqualWithAccuracy(-81.0, (query.getReal(column: 1)), accuracy: PRECISION_MAX_DELTA)
        XCTAssertEqualWithAccuracy(-79.6, (query.getReal(column: 2)), accuracy: PRECISION_MAX_DELTA)
        XCTAssertEqualWithAccuracy(35.0, (query.getReal(column: 3)), accuracy: PRECISION_MAX_DELTA)
        XCTAssertEqualWithAccuracy(36.2, (query.getReal(column: 4)), accuracy: PRECISION_MAX_DELTA)
        XCTAssertTrue(query.moveToNext())
        XCTAssertTrue(query.isAfterLast())
        XCTAssertFalse(query.moveToNext())
        
        query = md.query(sql: "SELECT * FROM demo_index WHERE id=1;")
        XCTAssertTrue(query.moveToFirst())
        XCTAssertEqual(1, query.getInt(column: 0))
        XCTAssertEqualWithAccuracy(-80.7749582, (query.getReal(column: 1)), accuracy: PRECISION_MAX_DELTA)
        XCTAssertEqualWithAccuracy(-80.7747392, (query.getReal(column: 2)), accuracy: PRECISION_MAX_DELTA)
        XCTAssertEqualWithAccuracy(35.3776136, (query.getReal(column: 3)), accuracy: PRECISION_MAX_DELTA)
        XCTAssertEqualWithAccuracy(35.3778356, (query.getReal(column: 4)), accuracy: PRECISION_MAX_DELTA)
        XCTAssertTrue(query.moveToNext())
        XCTAssertTrue(query.isAfterLast())
        XCTAssertFalse(query.moveToNext())
        
    }
    
    func givenAnRTreeDatabase() -> MadDatabase {
        let md = MadDatabase()
        let s = "CREATE VIRTUAL TABLE demo_index USING rtree(" +
            "id   INTEGER, " +
            "minX REAL, " +
            "maxX REAL, " +
            "minY REAL, " +
        "maxY REAL);"
        _ = md.exec(sql: s)
        return md
    }
    
    func givenValuesInserted(database md: MadDatabase) {
        _ = md.exec(sql: "INSERT INTO demo_index VALUES(1,-80.7749582,-80.7747392,35.3776136,35.3778356);")
        XCTAssertNil(md.getError())
    }
    
    func givenContentValuesInserted(database md: MadDatabase) {
        let cv = MadContentValues()
        cv.putInt(key: "id", value: 2)
        // NC 12th Congressional District in 2010
        cv.putReal(key: "minX", value: -81.0)
        cv.putReal(key: "maxX", value: -79.6)
        cv.putReal(key: "minY", value: 35.0)
        cv.putReal(key: "maxY", value: 36.2)
        XCTAssertTrue(md.insert(table: "demo_index", values: cv))
    }
    
}
