package io.madrona.madsqlite;

import android.content.ContentValues;

import java.io.Closeable;

@SuppressWarnings("WeakerAccess")
public final class Database implements Closeable {

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


    public Database() {
        nativePtr = JniBridge.openDatabase(null);
    }

    public Database(final String absPath) {
        nativePtr = JniBridge.openDatabase(absPath);
    }

    //endregion

    //region PRIVATE METHODS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //endregion

    //region PUBLIC METHODS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    public int exec(String query) {
        return JniBridge.exec(nativePtr, query);
    }

    public void insert(String table, ContentValues contentValues) {
        String[] keys = new String[contentValues.size()];
        Object[] values = new Object[contentValues.size()];
        int i = 0;
        for (String key: contentValues.keySet()) {
            keys[i] = key;
            values[i] = contentValues.get(key);
            ++i;
        }
        JniBridge.insert(nativePtr, table, keys, values);
    }

    public Cursor query(String query, String... args) {
        long cursorPtr = JniBridge.query(nativePtr, query, args);
        return new Cursor(cursorPtr);
    }

    public Cursor query(String query) {
        return query(query, (String[]) null);
    }

    //endregion

    //region ACCESSORS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //endregion

    //region {Closeable} ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    @Override
    public void close() {
        JniBridge.closeDatabase(nativePtr);
        nativePtr = 0L;
    }

    //endregion

    //region INNER CLASSES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //endregion

}
