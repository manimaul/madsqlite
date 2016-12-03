//
// Created by William Kamp on 12/2/16.
// Copyright (c) 2016 William Kamp. All rights reserved.
//
import Foundation
import MadSqlite

public class MadContentValues {

    internal let cv = MADSqliteFactory.contentValues()!

   /**
    * Adds a value to the set.
    *
    * @param key the name of the value to put.
    * @param value the data for the value to put.
    */
    public func putInt(key k: String, value v: Int) {
        cv.putInteger(k, withValue:  NSNumber(value: v))
    }

   /**
    * Adds a value to the set.
    *
    * @param key the name of the value to put.
    * @param value the data for the value to put.
    */
    public func putInt64(key k: String, value v: Int64) {
        cv.putInteger(k, withValue:  NSNumber(value: v))
    }

   /**
    * Adds a value to the set.
    *
    * @param key the name of the value to put.
    * @param value the data for the value to put.
    */
    public func putReal(key k: String, value v: Double) {
        cv.putReal(k, withValue:  NSNumber(value: v))
    }

   /**
    * Adds a value to the set.
    *
    * @param key the name of the value to put.
    * @param value the data for the value to put.
    */
    public func putReal(key k: String, value v: Float) {
        cv.putReal(k, withValue: NSNumber(value: v))
    }

   /**
    * Adds a value to the set.
    *
    * @param key the name of the value to put.
    * @param value the data for the value to put.
    */
    public func putString(key k: String, value v: String?) {
        cv.put(k, withValue: v)
    }

   /**
    * Adds a value to the set.
    *
    * @param key the name of the value to put.
    * @param value the data for the value to put.
    */
    public func putBlob(key k: String, value v: Data?) {
        cv.putBlob(k, withValue: v)
    }

   /**
    * Removes all values.
    */
    public func clear() {
        cv.clear()
    }

}
