package io.madrona.madsqlite;

import java.io.Closeable;

@SuppressWarnings("WeakerAccess")
public final class Cursor implements Closeable {

    //region CONSTANTS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //endregion

    //region FIELDS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    private long nativePtr;

    //endregion

    //region INJECTED DEPENDENCIES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //endregion

    //region INJECTED VIEWS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //endregion

    //region CONSTRUCTOR ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    Cursor(long ptr) {
        nativePtr = ptr;
    }

    //endregion

    //region PRIVATE METHODS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //endregion

    //region PUBLIC METHODS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    public boolean moveToFirst() {
        return JniBridge.moveToFirst(nativePtr);
    }

    public boolean moveToPosition(int position) {
        return JniBridge.moveToPosition(nativePtr, position);
    }

    public int getCount() {
        return JniBridge.getCount(nativePtr);
    }

    public boolean moveToNext() {
        return JniBridge.moveToNext(nativePtr);
    }

    public boolean isAfterLast() {
        return JniBridge.isAfterLast(nativePtr);
    }

    public String getString(int columnIndex) {
        return JniBridge.getString(nativePtr, columnIndex);
    }

    public byte[] getBlob(int columnIndex) {
        return JniBridge.getBlob(nativePtr, columnIndex);
    }

    public long getInt(int columnIndex) {
        return JniBridge.getInt(nativePtr, columnIndex);
    }

    public double getReal(int columnIndex) {
        return JniBridge.getReal(nativePtr, columnIndex);
    }

    //endregion

    //region ACCESSORS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //endregion

    //region {Closeable} ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    @Override
    public void close() {
        JniBridge.closeCursor(nativePtr);
        nativePtr = 0L;
    }

    //endregion

    //region INNER CLASSES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //endregion

}
