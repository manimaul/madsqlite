//
//  MadDatabase.swift
//  MadSqliteSwift
//
//  Created by William Kamp on 12/2/16.
//  Copyright © 2016 William Kamp. All rights reserved.
//
import Foundation
import MadSqlite

public class MadDatabase {

    private var md: MADDatabase!

    /**
     * @return a new in-memory sqlite database.
     */
    public init() {
        md = MADSqliteFactory.inMemoryDatabase()!
    }

    /**
     * Opens or creates a file system sqlite database.
     *
     * @param name the name of the database
     * @return a file system sqlite database
     */
    public init(name n: String) {
        md = MADSqliteFactory.databaseNamed(n)!
    }

    /**
     * Convenience method for inserting a row into the database.
     *
     * @param table the table to insert the row into.
     * @param values this map contains the initial column values for the row. The keys should be the column names and the
     * values the column values.
     * @return YES if the insert was successful.
     */
    public func insert(table t: String, values v: MadContentValues) -> Bool {
        return md.insert(t, with: v.cv)
    }

    /**
     * Query for results.
     *
     * @param sql - a sqlite query.
     * @return query results.
     */
    public func query(sql s: String) -> MadQuery {
        let q = md.query(s)!
        return MadQuery(query: q)
    }

   /**
    * Query for results with bound arguments.
    *
    * @param sql - a sqlite query containing arguments.
    * @param args You may include ?s in sql, which will be replaced by the values from args, in order that they appear in
    * the selection. The values will be bound as Strings.
    * @return query results.
    */
    public func query(sql s: String, args a: [String]) -> MadQuery {
        let q = md.query(s, withArgs: a)!
        return MadQuery(query: q)
    }

   /**
    * Execute a single SQL statement that is NOT a SELECT or any other SQL statement that returns data.
    *
    * @param sql the sql to execute.
    * @return the number of rows changed.
    */
    public func exec(sql s: String) -> Int {
        return md.exec(s)
    }

   /**
    * Get English-language text that describes an error associated with the most recent database API call.
    *
    * @return the most recent error or nil.
    */
    public func getError() -> String? {
        return md.getError()
    }

   /**
    * Begins a transaction. The changes will be rolled back if any transaction performed without being commited.
    */
    public func beginTransaction() {
        md.beginTransaction()
    }

   /**
    * Rolls back a begun transaction.
    */
    public func rollbackTransaction() {
        md.rollbackTransaction()
    }

   /**
    * Commits a begun transaction.
    */
    public func commitTransaction() {
        md.commitTransaction()
    }

}
