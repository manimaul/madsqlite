//
// Created by William Kamp on 12/2/16.
// Copyright (c) 2016 William Kamp. All rights reserved.
//
import Foundation
import MadSqlite

public class MadQuery {

    private var mq: MADQuery

    internal init(query q: MADQuery) {
        mq = q
    }

    /**
     * Move the query to the first row.
     * @return NO if the query is empty.
     */
    public func moveToFirst() -> Bool {
        return mq.moveToFirst()
    }

    /**
     * Move the query to the next row.
     * @return NO if the query is already past the last entry in the result set.
     */
    public func moveToNext() -> Bool {
        return mq.moveToNext()
    }

    /**
     * @return Returns whether the query is pointing to the position after the last row.
     */
    public func isAfterLast() -> Bool {
        return mq.isAfterLast()
    }

    /**
     * @param columnIndex the zero-based index of the target column.
     * @return the value of that column as a String.
     */
    public func getString(column i: Int32) -> String {
        return mq.getString(i)
    }

    /**
     * @param columnIndex the zero-based index of the target column.
     * @return the value of that column as data.
     */
    public func getBlob(column i: Int32) -> Data {
        return mq.getBlob(i)
    }

    /**
     * @param columnIndex the zero-based index of the target column.
     * @return the value of that column a integer.
     */
    public func getInt(column i: Int32) -> Int {
        return mq.getInt(i).intValue
    }

    /**
     * @param columnIndex the zero-based index of the target column.
     * @return the value of that column a integer.
     */
    public func getInt64(column i: Int32) -> Int64 {
        return  mq.getInt(i).int64Value
    }

    /**
     * @param columnIndex the zero-based index of the target column.
     * @return the value of that column as a double.
     */
    public func getReal(column i: Int32) -> Double {
        return mq.getReal(i).doubleValue
    }

}