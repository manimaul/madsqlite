package io.madrona.madsqlite;

import android.content.ContentValues;

import java.io.Closeable;
import java.io.File;

@SuppressWarnings("WeakerAccess")
public final class MadDatabase implements Closeable {

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


    public MadDatabase() {
        nativePtr = JniBridge.openDatabase(null);
    }

    public MadDatabase(final File dbFile) {
        nativePtr = JniBridge.openDatabase(dbFile.getAbsolutePath());
    }

    //endregion

    //region PRIVATE METHODS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //endregion

    //region PUBLIC METHODS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    public int exec(String query) {
        return JniBridge.exec(nativePtr, query);
    }

    public boolean insert(String table, ContentValues contentValues) {
        String[] keys = new String[contentValues.size()];
        Object[] values = new Object[contentValues.size()];
        int i = 0;
        for (String key: contentValues.keySet()) {
            keys[i] = key;
            values[i] = contentValues.get(key);
            ++i;
        }
        return JniBridge.insert(nativePtr, table, keys, values);
    }

    public MadQuery query(String query, String... args) {
        long cursorPtr = JniBridge.query(nativePtr, query, args);
        return new MadQuery(cursorPtr);
    }

    public MadQuery query(String query, Object... args) {
        String[] strArgs = null;
        if (args != null) {
            strArgs = new String[args.length];
            for (int i = 0; i < args.length; i++) {
                strArgs[i] = args[i].toString();
            }
        }
        return query(query, strArgs);
    }

    public MadQuery query(String query) {
        return query(query, (String[]) null);
    }

    public void beginTransaction() {
        JniBridge.beginTransaction(nativePtr);
    }

    public void rollbackTransaction() {
        JniBridge.rollbackTransaction(nativePtr);
    }

    public void commitTransaction() {
        JniBridge.commitTransaction(nativePtr);
    }

    public String getError() {
        String error = JniBridge.getError(nativePtr);
        if (error.isEmpty()) {
            return null;
        } else {
            return error;
        }
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
