package io.madrona.madsqlite;

enum JniBridge {

    //region CONSTANTS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    INSTANCE;

    private static final String MADSQLITE_LIB = "madsqlite-lib";
    static {
        System.loadLibrary(MADSQLITE_LIB);
    }

    //endregion

    //endregion

    //region Database ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    static native long openDatabase(String absPath);
    static native void closeDatabase(long ptr);
    static native boolean insert(long dbPtr, String table, String[] keys, Object[] values);
    static native long query(long dbPtr, String query, String[] args);
    static native int exec(long dbPtr, String sql);
    static native String getError(long dbPtr);
    static native void beginTransaction(long dbPtr);
    static native void rollbackTransaction(long dbPtr);
    static native void endTransaction(long dbPtr);

    //endregion

    //region Cursor ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    static native void closeCursor(long nativePtr);
    static native boolean moveToNext(long nativePtr);
    static native boolean isAfterLast(long nativePtr);
    static native String getString(long nativePtr, int columnIndex);
    static native byte[] getBlob(long nativePtr, int columnIndex);
    static native long getLong(long nativePtr, int columnIndex);
    static native double getReal(long nativePtr, int columnIndex);
    static native boolean moveToFirst(long nativePtr);

    //endregion

}
