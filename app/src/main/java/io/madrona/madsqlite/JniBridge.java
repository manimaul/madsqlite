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

    //endregion

    //region Cursor ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    static native void closeCursor(long nativePtr);

    //endregion

}
